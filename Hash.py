from Record import *
from Block import *

class Hash:
    def __init__(self, disk_name="Hash.cbd", indexBy=[]):
        self.r_block = Block(disk_name)
        self.w_block = Block(disk_name)
        self.indexes={}
        for i in indexBy:
            self.indexes.update({i:open(i+"_"+disk_name,"w+")})

    def insert(self, string):
        rec = Record(string)
        self.w_block.write(abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size, rec)
        self.w_block.persist(abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size)
        for i in self.indexes:
            self.indexes[i].write(getattr(rec,i)+" "+str(abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size)+"\n")
            self.indexes[i].flush()

    def join(self,other_heap,field):
        pos=0
        self.r_block.read(pos)
        while(self.r_block.records[0]):
            for i in self.r_block.records:
                if i=='\x00'*138:
                    break
                if field=="cpf": #if field is primary key cpf
                    other_heap.r_block.read(abs(hash(Record(i).cpf)//10**6)*self.w_block.max_size*self.w_block.record_size)
                    if other_heap.r_block.records[0]!='\x00'*138:
                        print(i+"\n"+str(other_heap.r_block.records[0])+"\n")
                else:
                    if field in self.indexes: #if field is indexed
                        for line in self.indexes[field]:
                            if getattr(Record(i),field)==line.split()[0]:
                                other_heap.r_block.read(line.split()[1])
                                for j in other_heap.r_block.records:
                                    if not j:
                                        break
                                    if getattr(Record(i),field)==getattr(Record(j),field):
                                        print(i+"\n"+j+"\n")
                    else:
                        print("The requested field is not supported.")
                        return
            pos+=self.r_block.max_size*self.r_block.record_size
            self.r_block.read(pos)

#a=Hash("teste1.cbd")
#a.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
#b=Hash("teste2.cbd")
#b.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
#a.join(b)
