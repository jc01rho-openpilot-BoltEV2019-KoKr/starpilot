# I Taught My Comma to Read Speed Limit Signs

<video controls playsinline preload="metadata" poster="assets/speed-limit-vision-demo-poster.jpg" style="width: 100%; max-width: 1280px;">
  <source src="assets/speed-limit-vision-demo.mp4" type="video/mp4">
</video>

[Watch the speed-limit vision demo](assets/speed-limit-vision-demo.mp4)

This whole project started because I was lazy.

If you’ve driven an HKG or Toyota vehicle in recent years, you’ve probably seen the dashboard automatically pick up speed limits using the camera. Coming from a car that didn't have this functionality, I was very jealous. Those cars can feed those speed limits directly into openpilot forks speed limit controllers. Mine couldn't.

The “solution” has been to manually add speed limits to Mapbox or OpenStreetMaps. It worked, but it was tedious. I live in rural Kansas, where my commute is almost entirely devoid of nerds contributing open source map data. I began mapping my commute when I first joined the project and within an hour said, “I ain't doin this”

We have an AI model that's good enough to drive our cars running on a smartphone chipset from years ago. How hard could it be to build one that just reads speed limit signs? I wanted StarPilot to look out the windshield, see a speed limit sign, and just know what it said.

That sounded simple enough.

It wasn’t.

The first prototype was basically held together with duct tape: I used all the public speed limit datasets I could find (glare and Lisa), some OpenCV, a little OCR, and a lot of wishful thinking. It could occasionally read a sign, but it missed 90% of them and produced enough false positives that you definitely wouldn’t want to trust it.

The important part wasn’t that it sucked - it was that it worked just well enough to start collecting better training data.

I run a fork of openpilot called StarPilot. We're heavily focused on tuning and testing wild ideas, which made my users the perfect candidates for this project.

Instead of relying on public datasets that barely resembled comma camera footage, StarPilot started collecting its own. Community members submitted routes from all over the country using bookmarks that were generated automatically when the model said "I think this might've been a sign," and every promising detection went through manual review. Eventually that grew into hundreds of gigabytes of real driving footage and thousands of carefully labeled speed limit signs.

From there it became an endless cycle:

- Train a better model.
- Mine more routes.
- Find more missed signs.
- Label them.
- Repeat.

The funny part is that training the neural network wasn’t actually the hardest problem.

The hard part was everything around it.

One of the biggest challenges wasn’t accuracy, it was speed. Every millisecond spent processing was another frame the model didn't have time to see. The faster it could process frames, the more chances it had to catch a sharp, readable speed limit sign before it disappeared. This was particularly imperative at night, when naturally camera frame rates drop alongside your chances of picking up a clear sign.

It’s slowly evolved from a proof of concept into a model that’s trained primarily on real comma footage instead of generic traffic sign datasets. It now runs entirely on-device, publishes vision-based speed limits directly into StarPilot, and no longer depends on OCR or manually maintaining map data.

And best of all…

While I'm too lazy to hand write hundreds of speed limit signs into OpenStreetMaps, this tool can now be used to automate the entire process, giving back to the open source mapping community that helps those in larger areas so well.  

Give my vision speed limits a try, or help continue to build a better one than mine! All info and training stack is available on the StarPilot repo.

---

*For a full LLM style, more technical breakdown for those interested in the process, please read below:*


## Teaching StarPilot to Read Speed Limit Signs

In March 2026, this project started with a practical question: could StarPilot use the road camera to recognize speed-limit signs, attach them to GPS data, and help fill gaps in OpenStreetMap?

The first answer was "probably." A clean 40 mph sign in recorded comma footage was large enough to detect and read. StarPilot already had access to the live road-camera stream through VisionIPC, ONNX models could run through OpenCV DNN, and the existing Speed Limit Controller already knew how to combine several sources. The pieces existed.

What did not exist was a model trained for this camera, a trustworthy dataset, an honest replay benchmark, or a runtime that could analyze enough frames without interfering with openpilot. Building those became the real project.

This is the story of how we went from a weak imported model that was barely useful for automatic bookmarks to a custom detector and classifier trained primarily from real comma footage, how community routes changed the quality of the data, and why model accuracy on a laptop turned out to be only half of the problem.

### The first prototype

The first live implementation used an imported Ultralytics-style checkpoint called `ayoubsa_best`. Its provenance was thin: the ONNX metadata identified it as a Kaggle-trained detector, but there was no training notebook or source dataset in the repository. More importantly, its classes were a poor fit for American roads. It knew speed limits in 10 mph increments, such as 20, 30, and 40, but not the common 25, 35, 45, 55, or 65 mph signs.

That led to a hybrid design. The model proposed a sign region, then lightweight OpenCV and OCR-like digit logic tried to read the crop. It was enough to prove the complete path:

1. Read the live road-camera stream.
2. Search the right side of the frame for likely signs.
3. Produce a candidate speed and confidence.
4. Confirm it over time.
5. Publish it as a selectable `Vision` source for the Speed Limit Controller.
6. Save debug frames and bookmarks for later training.

It was not yet a good speed-limit reader. It missed most signs, produced false positives, and struggled badly with 5 mph increments. But it could occasionally find real signs, which meant it could help us collect the data needed to replace itself.

That bootstrap capability mattered more than its initial accuracy.

### Public data gave us a starting point

We chose a two-stage architecture early: one model would answer "where is the speed-limit sign and what kind is it?" while another would answer "what number is printed on it?" Detection and reading are related, but they are not the same task. Keeping them separate let the detector learn the general shape and location of a sign without needing a separate object class for every posted speed.

Three public U.S. traffic-sign datasets formed the initial training base:

- [LISA](https://cvrr.ucsd.edu/lisa-traffic-signs-dataset) provided U.S. road scenes, 47 sign types, and 7,855 annotations across 6,610 frames. Its annotations also included useful information such as occlusion and whether a sign belonged to a side road.
- [GLARE](https://arxiv.org/abs/2209.08716) provided 2,157 U.S. traffic-sign images taken from 33 dashcam videos under strong sun glare. The paper itself demonstrated why mixed normal and glare training was important.
- [ARTS](https://swshah.w3.uvm.edu/vail/datasets.php), the Automotive Repository of Traffic Signs, provided additional U.S. signs in easy, challenging, and video-log configurations.

The clean first pass imported 3,078 ARTS images with 3,139 relevant boxes. When a working LISA archive was found, it added 1,577 images and 1,680 boxes, including 15, 25, 35, 45, 55, and 65 mph classes. GLARE was downloaded selectively to avoid pulling a large collection of unrelated checkpoints.


### More data made the first retrain worse

The first clean public-data retrain looked reasonable in conventional validation metrics and failed badly on real comma routes.

The stronger older model found a candidate in 9 of 39 bookmarked route windows. The clean public-data model found only 1 of 39. It also regressed the saved-frame suite. We restored the older model instead of promoting a checkpoint merely because it was newer or had better training curves.

The domain gap was larger than image dimensions suggested. LISA, GLARE, ARTS, and comma footage were all forward-looking road imagery, but they differed in lens distortion, mounting position, exposure, dynamic range, compression, motion blur, sign position, and the number of pixels available when a sign first appeared. Public data often contained a cleaner or more centered sign than the live comma pipeline would see.

This established a rule that guided every later pass: public data was useful for bootstrapping and preservation, but real comma footage had to dominate final training and evaluation.

### Turning StarPilot into a data engine

The next large improvement did not come from a new backbone. It came from collecting better data.

StarPilot gained an automatic training collector, automatic bookmarks, manual bookmarks, debug snapshots, route metadata, and tools to preserve full-resolution video segments. A route-bundling script verified that a contributed route was public, contained the required qlogs, rlogs, and `fcamera.hevc` files, and had the vision collector enabled before packaging it.

That allowed StarPilot users to contribute real driving data from different cars, cameras, roads, states, lighting conditions, and sign styles. Eventually, nearly 200 GB of zipped comma routes landed on disk. This was enormously more useful than another generic sign dataset because it matched the exact production domain:

- the same road camera and encoding path;
- the same wide-angle geometry;
- the same night exposure and motion blur;
- the same right-shoulder sign placement;
- the same live crop errors;
- and the same hard negatives seen by the runtime detector.

The model could then scan old routes, find likely signs and mistakes, and generate another review queue. A better model could rescan the same backlog and find candidates the weaker model had never seen. Each iteration improved not only the deployed model, but also the quality of the next dataset.

### Human review was the quality control

Automatic labels were never trusted blindly. A map transition did not prove that a sign was visible, a bookmark did not prove that the best frame had been selected, and a confident model prediction did not prove that the crop contained the correct sign.

The manual review UI evolved around throughput. Typing a number labeled a regulatory sign. Single-key shortcuts marked advisory (`a`), school-zone (`s`), regulatory (`r`), uncertain (`u`), or ignored/not-a-sign (`i` or `x`) samples. Enter or Space accepted a prediction. Reviewers could also redraw a bad bounding box.

Those details affected model quality directly:

- A readable but slightly imperfect crop was useful.
- A crop that showed only the minimum-speed portion of a 65/40 sign was not a valid 40 mph regulatory label.
- Stop signs and empty crops became hard negatives.
- Advisory signs were labeled explicitly, even though overall sign recall remained the product priority.
- Uncertain night crops were retained separately instead of being treated as equally strong labels.
- Repeated frames from the same sign track were deduplicated so one scene could not dominate the dataset.
- Incorrectly large or shifted boxes were redrawn once the review tool exposed that capability.

One labeling ambiguity forced a larger re-review: earlier sessions had not made regulatory versus advisory state clear enough. Rather than preserve potentially poisoned labels, affected advisory candidates were put back into the queue under the corrected UI contract.

This was active learning in a practical form: spend human time on disagreements, weak reads, false publishes, missed signs, bad boxes, and rare conditions, not on thousands of easy duplicate frames.

By one later OCR-free promotion audit, the backlog covered 80 routes and 366,946 sampled frames. The model under audit produced 34,260 candidates for rescoring, while the canonical review database contained 5,383 unique human-reviewed crops: 593 positive reads and 4,146 usable crop-level rejects, with the remainder reserved for uncertain or otherwise excluded decisions. The raw route collection was large, but those reviewed examples were the part that made it trustworthy.

### The architecture that survived

The current production path is model-only. OCR remains in the source tree for legacy compatibility and offline experiments, but both full-frame OCR and crop OCR are disabled for the active detector/classifier pipeline.

The deployed stack contains:

- A YOLO11n-derived detector exported as a fixed `256x256` ONNX model. It proposes regulatory, advisory, and school-zone speed-limit signs.
- A YOLO11n-classifier-derived `128x128` ONNX model. It predicts 15 through 75 mph in 5 mph increments and includes a learned reject class for crops that are not valid speed-limit reads.
- Runtime logic that evaluates several crop expansions, combines their support, applies geometry and sign-type checks, and confirms lower-confidence changes over multiple frames.
- A right-side region of interest, which reduces wasted work while retaining the part of U.S. road scenes where most applicable signs appear.

The detector is about 9.9 MB and the classifier about 5.9 MB. They remain separate ONNX files intentionally. Joining the graphs into one file would make packaging look tidier, but it would not eliminate the detector or classifier computation. Separate models also let us change detector resolution, classifier training, reject behavior, and crop strategy independently.

A third standalone reject model was tested and discarded. It added another inference pass without measurably improving the reviewed positives or surviving false positive. Folding rejection into the value classifier produced a better cost/accuracy tradeoff.

OCR was removed only after the model-only path could pass the preservation suites on its own. In the decisive audit, model consensus improved the targeted 20 mph events from 1/14 to 11/14 and the broader targeted set from 21/36 to 27/36 without regressing the established legacy suites. At that point, OCR's occasional rescue was no longer worth the latency, extra failure modes, and frames lost while the device waited for it to finish.

Direct-value detectors, smaller input sizes, MobileNet-style classifiers, optical-flow tracking, and multiple crop strategies were also tested. Some looked attractive on desktop metrics and failed where it mattered. In particular, a 224-pixel detector was faster but dropped the hometown 20 mph suite from 14/14 to 9/14. The 256-pixel detector remained the better production choice.

### Frame rate is part of accuracy

The most important evaluation lesson came from a route with seven manually bookmarked signs.

An early offline replay sampled the video at 5 fps and found several signs. The actual comma found almost none. The model files matched and the vision process was running, so the discrepancy initially looked mysterious.

The replay had been landing on lucky frames.

The camera produced 25 frames per second, but the live process only attempted inference every 0.4 seconds. When we replayed all 25 source frames while enforcing that real inference gate, the local result fell to 0 of 7, matching the drive. Halving the interval to 0.2 seconds moved the same honest replay to 5 of 7 candidate windows and 3 of 7 actual publishes.

From then on, a model was not evaluated only as a collection of independent images. Route replay had to include:

- source-frame timing;
- the measured detector and classifier cost;
- steady and follow-up inference intervals;
- temporal confirmation rules;
- CPU backoff;
- and the distinction between a candidate and a value actually published to the UI or controller.

This distinction explained many arguments over numbers. A candidate means the detector and reader noticed something in a sign window. A publish means the temporal and confidence gates accepted it as the live speed limit. A model can read a sign correctly once and still fail to publish if a weak read requires a second frame that the device never processes.

Later-frame mining showed why this mattered. One pass revisited 405 known sign events and extracted 939 clearer frames from later in their tracks. Combined with track-aware classifier training and a reduction from four classifier crops to three, the measured runtime suite improved from 247 to 265 correct publications, including a gain from 211 to 229 in the priority 30-65 mph range. Better frame selection and less per-frame work helped at the same time.

### Making it fit beside openpilot

The comma is already running camera processing, the main driving models, localization, controls, the UI, and vehicle communication. A speed-limit sidecar cannot assume an idle CPU.

The early hybrid pipeline could take roughly 1.5 seconds per frame when the detector, crop reader, and OCR paths all fired. At that cadence, signs could pass through their brief readable window without ever being analyzed. It also added enough CPU pressure to coincide with camera/model frame-sync errors and temporary `locationd` alerts on some night drives.

Changing process priority was not the solution. The daemon was already running at a very low scheduling priority. The useful changes were to remove OCR from production, restrict detection to the right-side ROI, shrink the models carefully, avoid the extra reject-model pass, add device-load backoff, and use a faster follow-up cadence after a candidate appeared.

The current runtime requests a 0.15-second steady interval and a 0.10-second follow-up interval, but inference cost is the real limiter. On two measured routes, the complete process sustained about 1.77 to 1.81 inferences per second. The detector alone took roughly 0.43 to 0.44 seconds, and each classifier crop could add about 0.066 seconds. A sign may receive only 4 to 13 analyzed frames in a seven-second approach window.

This is why "run it at 10 Hz" is not a configuration change. The process can ask for 10 Hz, but it cannot start the next inference until the current one finishes.

### Debugging the system, not just the model

Several apparent model regressions were actually system problems.


These failures led to better observability: model hashes, inference counts, interval reasons, detector and classifier timing, CPU backoff state, candidates, publications, and debug captures all became part of route analysis. We stopped asking only "is the model accurate?" and started asking "which exact model and runtime processed which exact frames, and what did it publish?"

### How we decide whether a model is better

The promotion process now uses several independent gates:

- Reviewed crop accuracy checks whether the classifier can read localized signs.
- Hard-negative sets contain parking signs, traffic signals, truck restrictions, taillights, and other shapes that previously caused false reads.
- A 100-event main route suite tests full candidate and publication behavior at measured comma cadence.
- A separate 34-event held-out suite guards against tuning directly to the main set.
- A hometown 20 mph suite protects a class that earlier models repeatedly missed.
- Legacy suites ensure that old wins do not disappear.
- Targeted night and glare replays test the conditions most likely to break normal validation assumptions.
- On-device timing and live routes remain the final authority.

Many experiments were rejected despite improving one number. A glare-focused model lost broader recall. A traffic-signal hard-negative detector fixed one false positive and lost legitimate 35 mph signs. A more aggressive reject-classifier update reduced errors and then changed enough timing to expose different false publishes. Conservative weight interpolation often produced the safest result because it taught a narrow correction without erasing the representation that already worked.

The drive currently contains 87 detector experiment directories and 72 classifier experiment directories. Those are not 159 successive improvements. They are the record of resolution bake-offs, failed hard-negative passes, direct-value experiments, night/glare runs, integrated-reject models, temporal-crop training, and interpolations that mapped the boundaries of the system.

### Where accuracy is now

The current classifier, internally called `distilled-moonstone v3`, improved the deployed route suite without changing model size or runtime cost:

| Runtime suite | Previous tree | Current model |
| --- | ---: | ---: |
| Main route publishes | 78/100 | **92/100** |
| Main wrong publishes | 0 | **0** |
| Held-out publishes | 24/34 | **26/34** |
| Hometown 20 mph signs | 14/14 | **14/14** |
| Hard sun-glare check | 70 mph published | **70 mph published** |

These denominators are manually confirmed sign events, not arbitrary video frames. `92/100` means the full runtime pipeline published the correct value in 92 of 100 known sign windows while running with measured comma timing. It does not mean the model is 92 percent accurate on every road or every possible sign.

In ordinary daylight scenes, current performance is very good. The model is now reliable when signs are reasonably exposed and readable, while extreme image quality and limited frame opportunities remain the dominant failures.

The current result is also substantially better than the first public-data prototype, which missed nearly every sign on several routes and sometimes produced only a single useful event in an entire drive.

### The next hard barriers

The remaining misses are unusually informative. Of the 18 main-suite events the current model does not publish:

- 6 never produce a correct candidate at measured cadence.
- 4 produce exactly one weak correct read, but cannot satisfy the two-read confirmation rule.
- At an idealized 6.7 Hz cadence, the same model recovers 7 of those 10 publishes, reaching a theoretical 97/100, but also introduces one wrong publish.
- The three stubborn cases are all 45 mph scenes: two remain unreadable even at ideal cadence, and one first reads 40 before seeing 45 too late.

That theoretical 97/100 is not a production accuracy claim. It is a diagnostic result showing that most remaining failures already contain a readable frame that the device does not process.

The next large improvement is therefore likely to come from throughput and temporal reuse, not from simply lowering confidence thresholds:

1. Make the detector materially faster without giving up the small-sign and 20 mph recall lost by the 224- and 192-pixel experiments.
2. After a detector finds a sign, track or cheaply reclassify that crop across nearby frames instead of paying for another full detector pass every time.
3. Investigate a more efficient inference backend or model architecture on comma hardware. Direct model microbenchmarks are useful, but the complete process and onroad CPU contention must remain the acceptance metric.
4. Add targeted, human-reviewed sequences for the remaining 45 mph failures, night ghosting, distant signs, and direct-sun approaches.
5. Improve sign applicability for minimum-speed, truck-only, school-zone, advisory, side-road, and exit-ramp signs without sacrificing the product's primary goal: finding normal regulatory speed limits.
6. Keep model-fingerprinted backlog mining so every promoted model can rescan old routes into an isolated review set without silently replacing canonical labels.

Night remains difficult because the camera often produces fewer sharp frames, motion blur can create double digits, and reflective signs may be detected while they are still too distant to read. Glare is difficult for the opposite reason: contrast collapses and sign edges disappear into the sky. Both problems require sequence-level examples, not just one selected crop.

### What we learned

This was never one long training run. It was the construction of a data and evaluation system.

Public datasets made the first detector possible. A weak model made automatic collection possible. StarPilot users supplied the camera-native diversity that public data could not. Human review turned model proposals into trustworthy labels. Full-cadence replay exposed timing mistakes that image metrics hid. Live device telemetry kept CPU and process failures from being mistaken for neural-network failures. Conservative promotion gates preserved hard-won behavior while narrow experiments improved specific weaknesses.

The result is already useful and, in ordinary scenes, often impressively accurate. The path to the next jump is also clearer than it was at the beginning. We do not mainly need another giant pile of generic sign images. We need to process more of the good frames the comma already sees, teach the remaining hard sequences carefully, and continue judging the complete on-device system rather than the model in isolation.

That is the difference between training a traffic-sign classifier and building a speed-limit reader that works in a car.

### Technical references

- Runtime implementation: [`starpilot/system/speed_limit_vision.py`](../starpilot/system/speed_limit_vision.py)
- Training runbook: [`docs/how-to/train-speed-limit-vision.md`](how-to/train-speed-limit-vision.md)
- Training, mining, review, and evaluation tools: [`scripts/speed_limit_vision`](../scripts/speed_limit_vision)
- Deployed model assets: [`starpilot/assets/vision_models`](../starpilot/assets/vision_models)
