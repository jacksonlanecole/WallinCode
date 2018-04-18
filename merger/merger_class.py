"""merger_class.py
Author : Jackson Cole
Affil  : Middle Tennessee State University
Purpose: The MergerRun class is useful for encapsulating all data
         and methods that are commonly used when interacting with a
         merger's data.

         There are general size and dimensions classes at the bottom as
         well. They do what they do.
"""

from data_tools import Structure
from galaxy import Galaxy
import os
from numpy import genfromtxt

class MergerRun:
    def __init__(self, path_to_info_file, n1_particles, n2_particles,
            run_number, init_run_string):
        """Constructor for Merger class:
        """
        self.info = self.make_info_dict(path_to_info_file)
        self.name            = self.info['name']
        self.height          = Size(int(self.info['imageheight']),
                                        None)
        self.width           = Size(int(self.info['imagewidth']),
                                        None)
        self.dimensions      = Dimensions(self.height, self.width)
        self.filename        = self.name + '.txt'
        self.humanscores_filename = self.name + '.humanscores.txt'
        self.run             = run_number
        self.init            = init_run_string
        self.structure_created = False
        self.target_dirs     = self.setup_structure()
        self.primary         = Galaxy(
                name      = self.info['pname'],
                particles = n1_particles,
                ra        = self.info['pra'],
                dec       = self.info['pdec'],
                xc        = self.info['pxc'],
                yc        = self.info['pyc'],)


        self.secondary         = Galaxy(
                name      = self.info['sname'],
                particles = n1_particles,
                ra        = self.info['sra'],
                dec       = self.info['sdec'],
                xc        = self.info['sxc'],
                yc        = self.info['syc'],)

        # None-type attibutes upon initialization
        self.scores        = None


    def make_info_dict(self, path_to_info_file):
        entries = []
        with open(path_to_info_file, 'r') as f:
            for line in f:
                if not (line.startswith('#') or line == '\n'):
                    line = line.rstrip().split('=')
                    entries.append("'{}': '{}'".format(line[0], line[1]))


        info = eval('{' + ', '.join(entries) + '}')
        return info



    def setup_structure(self):
        if self.structure_created == False:
            path_list = ['output',
                    self.name,
                    'run'+str(self.run + 1).zfill(4),
                    ]
            target_dir = Structure(path_list)
        else:
            print('Directory structure already created. Continuing...')
            target_dir = Structure(path_list)

        return target_dir



    def existing_structure(self):
        if os.path.exists(self.target_dir.full_path):
            self.structure_created = True
        else:
            self.structure_created = False


    def create(self):
        """This really just calls the structure create method. I'm sure
        there is a better way to do this.
        """
        self.target_dirs.create()


    def get_scores(self):
        scores = []
        path_to_target_file = './input/' + self.filename
        if os.path.exists(path_to_target_file):
            with open(path_to_target_file, 'r') as f:
                line = f.readline()
                while len(line.split('\t')[0].split(',')) != 1:
                    score_info = line.split('\t')[0].split(',')[1:4]
                    scores.append(score_info)
                    line = f.readline()

        else:
            print(path_to_target_file + ' does not exist.')

        self.scores = scores


    def write_scores(self):
        path_to = './output/' + self.name + '/'
        if os.path.exists(path_to + self.humanscores_filename):
            pass

        else:
            with open(path_to + self.humanscores_filename, 'w') as f:
                for score_list in self.scores:
                    f.write(','.join(score_list) + '\n')


class Size:
    def __init__(self, image_dim, actual_dim):
        """Constructor for a general size glass
        """
        self.image = image_dim
        self.real  = actual_dim

class Dimensions:
    def __init__(self, height, width):
        """Constructor for Dimensions class
        """
        self.image = [height.image, width.image]
        self.real  = [height.real, width.real]
