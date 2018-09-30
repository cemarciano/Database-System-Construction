const Leite = require('leite');
const leite = new Leite();

const N = 1e6;

function getRnd(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

const header = 'cpf;rg;email;dt_nasc;sexo;nome;salario'

var fs = require('fs');
var stream = fs.createWriteStream("data.csv");
stream.once('open', function(fd) {
  stream.write(`${header}\n`);
  for (let index = 0; index < N; index++) {
    stream.write(`${leite.pessoa.cpf()};` +
                 `${leite.pessoa.rg()};` + 
                 `${leite.pessoa.email()};` + 
                 `${leite.pessoa.nascimento({ string: true })};` +
                 `${leite.pessoa.sexo()};` +
                 `${leite.pessoa.nome({ nomeDoMeio: true })};` +
                 `${getRnd(1500, 10000).toFixed(2)}\n`);
  }
  stream.end();
});
