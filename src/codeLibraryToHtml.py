'''
Created on Dec 3, 2011
Used to generate Html list of Logicalmars Code Library 

@author: v-menlin
'''

import HTML
import os
path = r"C:\Users\v-menlin\Desktop\ACM\LogicalMarsLibrary\Test"

color = ['White', 'Yellow']
t = HTML.Table(header_row = ['Name', 'Link', 'Language', 'Description'])
baseurl = 'http://code.google.com/p/menglin-icpc-code-library/source/browse/icpcLibrary/'

count = 0
for (path, dirs, files) in os.walk(path, True, None):    
    for f in files:
        name = f.split(".")[0]
        count = count + 1
        
        bgcolor = color[count % 2]
        row = []
        row.append(HTML.TableCell(name, bgcolor))
        lk = HTML.link('(link)', baseurl + f)
        row.append(HTML.TableCell(lk, bgcolor))
        row.append(HTML.TableCell("C++", bgcolor))          
        row.append(HTML.TableCell(name.replace("_", " "), bgcolor))    
        t.rows.append(row)
        
htmlcode = str(t)
print htmlcode
