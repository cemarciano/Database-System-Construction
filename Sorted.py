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
        allRecords.sort()
        sortedFile = open(self.disk_name, "w")
        sortedFile.write("".join(allRecords))
        sortedFile.flush()
        # + indexing implementation

    def join(self, other_sorted, field, other_field=""):
        if not other_field:
            other_field=field
        pos, other_pos, pos_inside_block, other_pos_inside_block = 0, 0, 0, 0 #*_inside_block marks a record inside a block
        self.r_block.read(pos)
        while(self.r_block.records[0]):
            other_sorted.r_block.read(other_pos)
            while(other_sorted.r_block.records[0]):
                if(getattr(Record(self.r_block.records[pos_inside_block]),field)==getattr(Record(other_sorted.r_block.records[other_pos_inside_block]),other_field)):
                    print(self.r_block.records[pos_inside_block]+"\n"+other_sorted.r_block.records[other_pos_inside_block]+"\n")
                    pos_inside_block+=1 #pair found, moves left table's pointer
                else:
                    if(getattr(Record(self.r_block.records[pos_inside_block]),field)<getattr(Record(other_sorted.r_block.records[other_pos_inside_block]),other_field)):
                          pos_inside_block+=1 #moves left table's pointer
                    else:
                          other_pos_inside_block+=1 #moves right table's pointer
                if(pos_inside_block>=self.r_block.max_size): #loads left table's next block
                    pos_inside_block=0
                    pos+=self.r_block.max_size*self.r_block.record_size
                    self.r_block.read(pos)
                if(other_pos_inside_block>=other_sorted.r_block.max_size): #loads right table's next block
                    other_pos_inside_block=0
                    other_pos+=other_sorted.r_block.max_size*other_sorted.r_block.record_size
                    other_sorted.r_block.read(pos)
                

# a = Sorted()
# a.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
# a.insert("33331111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
# a.insert("22222222222;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")

a=Sorted("teste1.cbd")
a.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
a.insert("33333333333;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
b=Sorted("teste2.cbd")
b.insert("22222222222;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")

a.join(b, "nome")
