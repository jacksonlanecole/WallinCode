# WallinCode

## run_multiple script
This fork of WallinCode contains run_multiple, a python3 script that runs specific runs or specific ranges of runs from the Overlapping galaxy pairs table at [https://data.galaxyzoo.org/mergers.html](https://data.galaxyzoo.org/mergers.html).

To use run_multiple, enter

`./run_multiple file_containing_data.txt`

The script will then ask if you want to run only one run from the file or multiple. Then you will be asked for the run numbers for a specific range of runs. The run numbers correspond to the line number in the file. The output files are then organized in the following way:

`./ouput/target_name(which is really the filename preceeding the extension)/run_number`
