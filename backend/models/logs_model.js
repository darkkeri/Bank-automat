const db = require('../database');

const logs = {
    getAllLogs(callback){
        return db.query("SELECT * FROM logs", callback);
    },
    addLogs(newLogs, callback){
        return db.query("INSERT INTO logs VALUES(?,?,?,?,?)",
        [newLogs.idLogs,newLogs.date,newLogs.event,newLogs.amount,newLogs.idAccount], callback);
    },
    updateLogs(log, updateData, callback){
        return db.query("UPDATE logs SET date=?, event=?, amount=?, idAccount=? WHERE idLogs=?",
        [updateData.date, updateData.event, updateData.amount, updateData.idAccount, log],callback);
    },
    deleteLogs(log, callback){
        return db.query("DELETE FROM logs WHERE idLogs=?",[log],callback);
    },
    getOneLog(log, callback){
        return db.query("SELECT * FROM logs WHERE idLogs=?",[log],callback);
    }
}

module.exports = logs;