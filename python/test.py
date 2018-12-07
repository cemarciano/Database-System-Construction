from Heap import *
#from Hash import *
#from Sorted import *

import os, random

"""Loads toy data from file"""
data=open("data-generation/sample100.csv",encoding="utf8")
toLoad=[line.rstrip("\n") for line in data][1:]

"""Inserts data into database"""
if os.path.exists("table1.cbd"):
    os.remove("table1.cbd")
if os.path.exists("table2.cbd"):
    os.remove("table2.cbd")
table1=Heap("table1.cbd",indexBy=["nome"])
table2=Heap("table2.cbd",indexBy=["nome"])
for i in toLoad:
    #table1.insert(i)
    table2.insert(i)
for i in range(10): #fits in memory
    table1.insert(random.choice(toLoad))

"""Tests joins"""
table1.join(table2,"nome")
print(table1.r_block.n_op)
print(table2.r_block.n_op)

"""Finishes"""
del table1, table2
