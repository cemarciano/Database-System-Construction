class Record:
    def __init__(self, string):
        """ Split argument (record) by ; character and set member variables """
        field = string.split(';')
        self.cpf = field[0]
        self.rg = field[1]
        self.email = field[2] + '\0'*(40 - len(field[2]))
        self.nasc = field[3]
        self.sexo = field[4] + '\0'*(9 - len(field[4]))
        self.nome = field[5] + '\0'*(40 - len(field[5]))
        self.salario = field[6] + '\0'*(10 - len(field[6]))

    def __str__(self):
        return self.cpf+self.rg+self.email+self.nasc+self.sexo+self.nome+self.salario
