# WallinCode

## Table of Contents
- [Overview](#overview)
- [Get Started](#getstarted)
- [Targets](#targets)
- [Current state](#current)
- [run_multiple script](#run_multiple_script)
- [data_tools](#data_tools)
- [image_creator](#image_creator)
- [comparison_code](#comparison_code)
- [plotting_test](#plotting_test)
- [make_real](#make_real)

## Overview<a id="overview">
This is the development branch of a fork of
[Wallincode](https://github.com/JSPAM-Manga/WallinCode).

The recent developments in this fork of JSPAM-Manga focus on creating a machine
scoring mechanism for comparing
rendered galaxy merger models to the morphology of their real counterparts.
These machine scores can then be used in conjunction with citizen science
efforts to score these same models, effectively reducing the human interaction
time needed to determine whether a particular model is "good" or "bad." Further,
the availability of a machine scoring mechanism will open the door to
incorporation of various machine learning algorithms to throw out bad models,
thereby removing the need for a human-in-the-loop altogether.


## Get Started<a id="getstarted">
To simplify things, we have included the entire `virtualenv-15.2.0` package
found at https://pypi.python.org/pypi/virtualenv/15.2.0. To setup
the virtual environment install the required packages, issue the following
commands from the root directory:

```
python virtualenv-15.2.0/virtualenv.py -p python3 env
```

At this point, the virtualenv can be activated by entering

```
source env/bin/activate
```

To install the required packages, issue the following command:

```
pip install -r requirements.txt
```


## Target Images<a id="target_images">
Real images of the target galaxies are contained in the `target_images`
directory. These are to be used as the reference images for comparison in
testing.

To my knowledge, the original dataset is based off of images from SDSS DR7, but
the image directory will contain processed images of those same targets using
data from SDSS DR14.


## Current State of Things<a id="current">
Currently, [run_multiple](#run_multiple_script) is set up to complete runs of
basic_run interactively.

There is now a Python [data_tools](#data_tools) package that contains
- structure.py: This is a general_purpose directory structure creator.
- get_target_data.py: This is a module that scrapes the mergers.html page
for links to the zipped target data files. This may not belong in the package,
but as of right now that is its home.

A C++ image_creator and comparison code have also been added.

## run_multiple script<a id="run_multiple_script">
This fork of WallinCode contains run_multiple, a python3 script that runs
specific runs or specific ranges of runs from the Overlapping galaxy pairs
table at
[https://data.galaxyzoo.org/mergers.html](https://data.galaxyzoo.org/mergers.html).
I suggest placing the data files in a directory within the working directory
and copying the necessary files from the input directory when needed.

To use run_multiple, enter

`./run_multiple file_containing_data.txt`

The script will then ask if you want to run only one run from the file or multiple.
Then you will be asked for the run numbers for a specific range of runs. The run
numbers correspond to the line number in the file. The output files are then
organized in the following way:

`./ouput/target_name(which is really the filename preceeding the extension)/run_number`

## data_tools<a id="data_tools">
This is a package that will contain any data tools that can be written as a
general purpose tool. Right now, it contains
- structure.py: This is a general_purpose directory structure creator.
- get_target_data.py: This is a module that scrapes the mergers.html page
for links to the zipped target data files. This may not belong in the package,
but as of right now that is its home.

## image_creator<a id="image_creator">

## comparison_code<a id="comparison_code">

## plotting_test<a id="plotting_test">
This is the temporary name of a python3 script that will produce 2D and 3D plots
of a particular time step. It takes one argument as shown below:

`./plotting_test a.101`

I recommend symlinking plotting_test in general to

`./output/target/run_number/.`

where the data files for each time step are located (i.e. a.000, a.001, ...).
This directory structure is created by **run_multiple**.

There is also an option to produce a gif of the 3D runs (not working at the
moment, not sure what the problem is.)

## make_real<a id="make_real">
This is a python script that intends to produce realistic images of a galaxy end
state output. As of right now, it is in the beginning stages and only calls a
simple gaussian filter over the whole image and a median filter.

# Notes
All development is currently being done on the
[development](https://github.com/jacksonlanecole/WallinCode/tree/development)
branch of this fork. Check it out there!
