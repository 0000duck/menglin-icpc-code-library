'''
Created on Dec 3, 2011

@author: v-menlin
'''

# Used to remove duplicated names in my phone contacts

import codecs
import os
baseurl = "D:\\workspace\\testpy\\icpcLibrary\\"

for paths, dirs, files in os.walk(baseurl):
    for f in files:
        infilename = baseurl + f
        outfilename = baseurl + f
        try:        
            fin = codecs.open(infilename, 'r', encoding = 'gb18030')
            content = "\n".join(fin.readlines())
            fin.close()
            fout = open(outfilename, 'w')
            fout.write(content.encode('utf-8'))
            fout.close()
        except UnicodeDecodeError:
            print f
            