const mysql = require('mysql2');

const conn ="mysql://bankuser:bankpass@127.0.0.1:3306/pankkiautomaatti";

const connection = mysql.createPool(conn);

module.exports = connection;