# Longitudinal Maneuvers Testing Tool

Test your vehicle's longitudinal control tuning with this tool. The tool will test the vehicle's ability to follow a few longitudinal maneuvers and includes a tool to generate a report from the route.

<details><summary>Sample snapshot of a report.</summary><img width="600px" src="https://github.com/user-attachments/assets/d18d0c7d-2bde-44c1-8e86-1741ed442ad8"></details>

## Instructions

1. Check out a development branch such as `master` on your comma device.
2. Locate either a large empty parking lot or road devoid of any car or foot traffic. Flat, straight road is preferred. The full maneuver suite can take 1 mile or more if left running, however it is recommended to disengage openpilot between maneuvers and turn around if there is not enough space.
3. Arm maneuver mode from The Pond (`Tools -> Long Maneuvers -> Start / Arm`) or by setting this parameter manually:

   ```sh
   echo -n 1 > /data/params/d/LongitudinalManeuverMode
   ```

4. Turn your vehicle back on. This FrogPilot branch now shows on-road popup status for maneuver progress. You can still verify markers from logs with:

   ```sh
   python selfdrive/debug/filter_log_message.py --level WARNING
   ```
   You should see `LONG_MANEUVER_MODE|state=STARTED` and maneuver start/end markers.
   For GM pedal-long cars, you should also see phase markers:
   - `LONG_MANEUVER_PHASE|name=pedal_only|paddleMode=off`
   - `LONG_MANEUVER_PHASE|name=pedal_plus_paddle|paddleMode=force`

5. Ensure the road ahead is clear, as openpilot will not brake for any obstructions in this mode. Once you are ready, press "Set" on your steering wheel to start the tests. Typical runtime is about 4 minutes for the base suite and can be ~8-10 minutes for GM pedal-long A/B runs. If you need to pause the tests, press "Cancel" on your steering wheel. You can resume the tests by pressing "Resume" on your steering wheel. 

   **Note:** For GM cars, it is recommended to hold down the resume button for all low-speed tests (starting, stopping and creep) to avoid the car entering standstill.
   **Note:** For GM pedal-long cars (pedal interceptor + regen paddle), the maneuver suite automatically runs A/B phases:
   - `pedal-only` (`LongitudinalManeuverPaddleMode=off`)
   - `pedal+paddle` (`LongitudinalManeuverPaddleMode=force`)
   It also includes:
   - Additional `-2.0` and `-2.5 m/s^2` brake steps as required checks (`-4.0` is informational due to pedal/regen limits).
   - Low-speed stop-envelope sweeps (8/12/16/20 mph starts) to quantify terminal stop authority.
   - Terminal stop probes (ramped/late strong regen request) to measure end-of-stop behavior.
   - Paddle blend probes to measure on/off transition smoothness and jerk around paddle edges.

   ![cog-clip-00 01 11 250-00 01 22 250](https://github.com/user-attachments/assets/c312c1cc-76e8-46e1-a05e-bb9dfb58994f)

6. When testing is complete, `maneuversd` logs `LONG_MANEUVER_MODE|state=FINISHED` in `logMessage` and automatically disables `LongitudinalManeuverMode` so normal planning resumes. Complete the route by pulling over and turning off the vehicle.

7. Visit https://connect.comma.ai and locate the route(s). They will stand out with lots of orange intervals in their timeline. Ensure "All logs" show as "uploaded."

   ![image](https://github.com/user-attachments/assets/cfe4c6d9-752f-4b24-b421-4b90a01933dc)

8. Gather the route ID and then run the report generator. The file will be exported to the same directory:

    ```sh
    $ python tools/longitudinal_maneuvers/generate_report.py 57048cfce01d9625/0000010e--5b26bc3be7 'pcm accel compensation'

    processing report for LEXUS_ES_TSS2
    plotting maneuver: start from stop, runs: 4
    plotting maneuver: creep: alternate between +1m/s^2 and -1m/s^2, runs: 2
    plotting maneuver: gas step response: +1m/s^2 from 20mph, runs: 2

    Report written to /home/batman/openpilot/tools/longitudinal_maneuvers/longitudinal_reports/LEXUS_ES_TSS2_57048cfce01d9625_0000010e--5b26bc3be7.html
    ```

   For GM pedal-long routes, the report now adds concrete tuning tables:
   - **Low-Speed Stop Envelope**:
     - achieved/target decel ratio
     - terminal ratio in 0.2–2.0 m/s
     - linger time in 0.2–1.5 m/s
     - rollout distance after `shouldStop`
     - numeric recommendations for:
       - low-speed `regen_gain_ratio` percent increase
       - low-speed `accel_min` delta
       - stop-margin increase (`IncreasedStoppingDistance` / planner stop margin)
     - per-run **tuning hint** for what to adjust next
   - **Paddle Blend Transition Probe**:
     - regen edge count
     - max jerk near edges
     - max command/output step at edges
     - numeric recommendations for:
       - blend-step reduction %
       - press/release confirm-frame increase
     - per-run **tuning hint** for blend/debounce/rate-limit changes

You can reach out on [Discord](https://discord.comma.ai) if you have any questions about these instructions or the tool itself.
