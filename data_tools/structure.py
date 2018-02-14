from os import path, mkdir

class structure:
    def __init__(self, path_list):
        '''
        Constructor for this class:
            This class takes a list as an argument that contains the
            directory structure that should be created.
            The path tuple should have the form
            path_tuple = ('root', 'child_1', 'child_2', ...)
        '''
        self.paths = self.get_structure_strings(path_list)
        self.full_path = './'+'/'.join(i for i in path_list) + '/'


    def get_structure_strings(self, path_list):
        paths = []
        for i in range(len(path_list)):
            paths.append('./' + '/'.join(j for j in path_list[:i+1]))

        return paths


    def create(self):
        for i, path_name in enumerate(self.paths):
            if path.isdir(path_name) == False:
                for j in self.paths[i:]:
                    mkdir(j)
