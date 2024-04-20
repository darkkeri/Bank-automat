const db = require('../database');

const account = {
    getAllAccount(callback){
        return db.query("SELECT * FROM account", callback);
    },
    addAccount(newAccount, callback){
        return db.query("INSERT INTO account VALUES(?,?,?,?)",
        [newAccount.idAccount, newAccount.balance, newAccount.accountnumber, newAccount.accounttype], callback);
    },
    updateAccount(id_, updateData, callback){
        return db.query("UPDATE account SET idAccount=?, balance=?, accountnumber=?, accounttype=? WHERE idAccount=?",
        [updateData.idAccount, updateData.balance, updateData.accountnumber, updateData.accounttype, id_], callback);
    },
    deleteAccount(id_, callback){
        return db.query("DELETE FROM account WHERE idAccount=?",[id_],callback);
    },
    getOneAccount(id_, callback){
        return db.query("SELECT * FROM account WHERE idAccount=?",[id_],callback);
    },
    getAccountByType(idCards, type, callback){
        return db.query("SELECT account.idAccount FROM cards INNER JOIN card_account ON cards.idCards = card_account.idCards INNER JOIN account ON card_account.idAccount = account.idAccount WHERE cards.idCards=? AND type=?",[idCards, type], callback);
    }
}   

module.exports = account;