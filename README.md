# WallinCode

## run_multiple script
This fork of WallinCode contains run_multiple, a python3 script that runs specific runs or specific ranges of runs from the Overlapping galaxy pairs table at [https://data.galaxyzoo.org/mergers.html](https://data.galaxyzoo.org/mergers.html). I suggest placing the data files in a directory within the working directory and copying the necessary files from the input directory when needed.

To use run_multiple, enter

`./run_multiple file_containing_data.txt`

The script will then ask if you want to run only one run from the file or multiple. Then you will be asked for the run numbers for a specific range of runs. The run numbers correspond to the line number in the file. The output files are then organized in the following way:

`./ouput/target_name(which is really the filename preceeding the extension)/run_number`

## plotting_test
This is the temporary name of a python3 script that will produce 2D and 3D plots of a particular time step. It takes one argument as shown below:

`./plotting_test a.101`

I recommend symlinking plotting_test in general to

`./output/target/run_number/.`

where the data files for each time step are located (i.e. a.000, a.001, ...). This directory structure is created by **run_multiple**.

There is also an option to produce a gif of the 3D runs (not working at the moment, not sure what the problem is.)
