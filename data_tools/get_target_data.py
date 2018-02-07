import requests
from bs4 import BeautifulSoup as bs
import urllib.request
import gzip
from os import remove

def get_target_data(dest_path):
    _base = 'https://data.galaxyzoo.org/'
    _URL = _base + 'mergers.html'
    r = requests.get(_URL)

    #print(r)
    soup = bs(r.text, 'lxml')
    #print('----------------------------------------')
    #print(soup)
    #f = open('temptest.txt', 'w')
    paths_for_url = []
    target_names = []

    for link in [link for link in soup.findAll(name = 'a')
        if 'parameter_files' in str(link)]:
        link = str(link)
        path_for_url = link[link.find('galaxy-'):link.find('.txt.gz') +
                len('.txt.gz')]
        target_name = link[link.find('r_files/') + len('r_files/'):
                link.find('_combined')]
        paths_for_url.append(path_for_url)
        target_names.append(target_name)
        #print(target_name)
        #print(path_for_url)
        #f.write('{number}: {link}\n'.format(number = i, link = link))

    print('Below will appear the list of available targets.')
    input('Please press [ENTER].')
    print('\nNumber\tTarget Name')
    for i, target in enumerate(target_names):
        print('{number}:\t{target}'.format(number = i + 1,\
                target = target))

    target_wanted = \
            input('Please enter the number corresponding to a target to'
            'download the associated data.\n'
            'Enter "ALL" to download and upzip all targets to input'
            'directory.\n> ')
    if (target_wanted != 'ALL'):
        target_to_download = [int(target_wanted) - 1]
        target_name = target_names[int(target_wanted) - 1]
    elif (target_wanted == 'ALL'):
        target_to_download = list(range(len(paths_for_url)))
        target_name = target_names

    
    for target_number, target in zip(target_to_download, target_name):
        target_gz = path + '{}.txt.gz'.format(target_name)
        urllib.request.urlretrieve(_base + paths_for_url[target_number],
                target_gz)
        with gzip.open(target_gz, 'rb') as infile:
            with open(target_gz[:-3], 'wb') as outfile:
                for line in infile:
                    outfile.write(line)

        remove(target_gz)


    #download_url = _base + paths_for_url[target_wanted]
    #print(download_url)


get_target_data('input')
