const db = require('../database');
const bcryptjs=require('bcryptjs');

const cards = {
    getAllCards(callback){
        return db.query("SELECT * FROM cards", callback);
    },
    addCards(newCards, callback){
        bcryptjs.hash(newCards.pincode,10,function(err,hashedpin){
            return db.query("INSERT INTO cards VALUES(?,?,?,?,?,?,?)",
            [newCards.idCards,newCards.cardnumber,hashedpin,newCards.type,newCards.tries,newCards.active,newCards.creditlimit], callback);
        });
        },
    updateCards(idCards, updateData, callback){
        bcryptjs.hash(updateData.pincode,10,function(err,hashedpin){
        return db.query("UPDATE cards SET cardnumber=?, pincode=?, type=?, tries=?, active=?, creditlimit=? WHERE idCards=?",
        [updateData.cardnumber, hashedpin, updateData.type, updateData.tries, updateData.active, updateData.creditlimit, idCards],callback);
        });
    },
    deleteCards(idCards, callback){
        return db.query("DELETE FROM cards WHERE idCards=?",[idCards], callback);
    },   
    getOneCard(idCards, callback){
        return db.query("SELECT * FROM cards WHERE idCards=?",[idCards],callback);
    },
    getCardIdByCardnum(cardnumber,callback){
        return db.query("SELECT idCards FROM cards WHERE cardnumber=?",[cardnumber], callback);
    },
    login(idCards, callback){
        return db.query("SELECT pincode FROM cards WHERE idCards=?",[idCards],callback);
    },
    putTries(idCards,triesUnResettinator, callback){
        return db.query("CALL putTries(?,?)",[idCards,triesUnResettinator], callback);
    }
}



module.exports = cards;