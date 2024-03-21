const db = require('../database');

const logs = {
    getAllLogs(callback){
        return db.query("SELECT * FROM logs", callback);
    },
    addLogs(newLogs, callback){
        return db.query("INSERT INTO logs VALUES(?,?,?,?,?)",
        [newLogs.idLogs,newLogs.date,newLogs.event,newLogs.amount,newLogs.idAccount], callback);
    }
}

module.exports = logs;