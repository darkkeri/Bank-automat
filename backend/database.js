const mysql = require('mysql2');

const conn ="mysql://bankuser:bankpass@127.0.0.1:3306/atm";

const connection = mysql.createPool(conn);

module.exports = connection;