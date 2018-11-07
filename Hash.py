from Record import *
from Block import *

class Hash:
    def __init__(self, disk_name="Hash.cbd"):
        self.r_block = Block(disk_name)
        self.w_block = Block(disk_name)

    def insert(self, string):
        rec = Record(string)
        self.w_block.write(abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size, rec)
        self.w_block.persist(abs(hash(rec.cpf)//10**6))

    def join(self,other_heap): #apenas para join de cpf; para demais campos, eh necessario usar indice
        pos=0
        self.r_block.read(pos)
        while(self.r_block.records[0]!=''):
            for i in self.r_block.records:
                if i=='\x00'*138:
                    break
                other_heap.r_block.read(abs(hash(Record(i))//10**6)*self.w_block.max_size*self.w_block.record_size)
                if other_heap.r_block.records[0]!='\x00'*138:
                    print(i+"\n"+str(other_heap.r_block.records[0])+"\n")
            pos+=self.r_block.max_size*self.r_block.record_size
            self.r_block.read(pos)

a=Hash("teste1.cbd")
a.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
b=Hash("teste2.cbd")
b.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
a.join(b)
