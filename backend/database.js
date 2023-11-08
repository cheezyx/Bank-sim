const mysql = require('mysql2');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'bankdatabase',
  password: 'bankdatabasepass',
  database: 'bankdatabase'
});
module.exports = connection;