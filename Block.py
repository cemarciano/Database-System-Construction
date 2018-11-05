from Record import *


class Block:
    def __init__(self, disk_name):
        """ Open disk file in write/read mode and set number of operations to 0 """
        self.disk = open(disk_name, "w+")  # Disk file
        self.max_size = 8  # Size of block
        self.n_op = 0  # Number of operations
        self.records = []  # List of records

    def __del__(self):
        self.persist(self.disk.tell())
        self.disk.close()

    def persist(self, pos):
        self.n_op += 1
        self.disk.seek(pos)
        for record in self.records:
            self.disk.write(record)
        self.disk.flush()
        self.records = []

    def write(self, pos, record):
        if (len(self.records) >= self.max_size):
            self.persist(pos)
        self.records += [record]

    def read(self, pos):
        self.n_op += 1
        self.records = []
        self.disk.seek(pos)
        while (len(self.records) < self.max_size):
            self.records += [self.disk.read(138)]

# r = Record("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
# b = Block("out.txt")
# b.write(0, str(r))
# b.persist(0)
# b.read(0)