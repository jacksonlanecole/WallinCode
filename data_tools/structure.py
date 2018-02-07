from os import path, mkdir


class structure:
    def __init__(self, structure_file):
        '''Constructor for this class'''
        self.structure_elements = \
                self.read_structure_file(structure_file)


    def read_structure_file(self, structure_file):
        structure_elements = []
        with open(structure_file, 'r') as f:
            for line in f:
                line_list = line.rstrip('\n').split(' ')
                structure_elements.append(line_list)

        return structure_elements

    '''
    def create(self, depth_id, root_name, dir_name):
        if path.isdir('./{}'.format(root_name)) == False:
            mkdir('./{}'.format(root_name))


    def is_root(self, depth_id):
        if (depth_id == 'r'):
            return True
        else:
            return False

    def how_deep(self, line):
        depth_id = line.split(' ')[0]
        if (depth_id == 'r'):
            return
        name = line.split(' ')[1]

        return is_root, depth, variable



    def check_path(self, depth, root):




    def create_root(self, root_name):
        if path.isdir('./{}'.format(root_name)) == False:
            mkdir('./{}'.format(root_name))

    '''
def main():
    galaxies = structure('outputstructure.txt')
    print(galaxies.structure_elements)

main()
