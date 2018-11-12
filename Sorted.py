from Record import *
from Block import *


class Sorted:
    def __init__(self, disk_name="Sorted.cbd", indexBy=[]):
        self.disk_name = disk_name
        self.r_block = Block(disk_name)
        self.w_block = Block(disk_name)
        self.indexes = {}
        for i in indexBy:
            self.indexes.update({i: open(i+"_"+disk_name, "w+")})

    def __del__(self):
        for i in self.indexes:
            self.indexes[i].close()

    def insert(self, string):
        rec = Record(string)
        self.w_block.write(self.w_block.disk.tell(), rec)
        self.w_block.persist(self.w_block.disk.tell())
        allRecords = []
        pos = 0
        self.r_block.read(pos)
        while self.r_block.records[0]:
            allRecords += self.r_block.records
            pos += self.r_block.max_size*self.r_block.record_size
            self.r_block.read(pos)
        # print(allRecords) #must read registers properly, considering their size
        allRecords.sort()
        # print(allRecords)
        sortedFile = open(self.disk_name, "w")
        sortedFile.write("".join(allRecords))
        sortedFile.flush()
        # + indexing implementation


# a = Sorted()
# a.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
# a.insert("33331111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
# a.insert("22222222222;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
