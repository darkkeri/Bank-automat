const db = require('../database');
//const bcryptjs=req('bcryptjs');

const cards = {
    getAllCards(callback){
        return db.query("SELECT * FROM cards", callback);
    },
    addCards(newCards, callback){
        return db.query("INSERT INTO cards VALUES(?,?,?,?,?,?,?)",
        [newCards.idCards,newCards.cardnumber,newCards.pincode,newCards.type,newCards.tries,newCards.active,newCards.creditlimit], callback);
        },
    updateCards(idCards, updateData, callback){
        return db.query("UPDATE cards SET cardnumber=?, pincode=?, type=?, tries=?, active=?, creditlimit=? WHERE idCards=?",
        [updateData.cardnumber, updateData.pincode, updateData.type, updateData.tries, updateData.active, updateData.creditlimit, idCards],callback);
    },
    deleteCards(idCards, callback){
        return db.query("DELETE FROM cards WHERE idCards=?",[idCards], callback);
    }   

}

module.exports = cards;