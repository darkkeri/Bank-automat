const db = require('../database');

const account = {
    getAllAccount(callback){
        return db.query("SELECT * FROM account", callback);
    },
    addAccount(newAccount, callback){
        return db.query("INSERT INTO account VALUES(?,?,?)",
        [newAccount.idAccount, newAccount.balance, newAccount.accountnumber], callback);
    },
    updateAccount(id_, updateData, callback){
        return db.query("UPDATE account SET idAccount=?, balance=?, accountnumber=? WHERE idAccount=?",
        [updateData.idAccount, updateData.balance, updateData.accountnumber, id_], callback);
    },
    deleteAccount(id_, callback){
        return db.query("DELETE FROM account WHERE idAccount=?",[id_],callback);
    }
}   

module.exports = account;