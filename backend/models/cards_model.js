const db = require('../database');
//const bcryptjs=req('bcryptjs');

const cards = {
    getAllCards(callback){
        return db.query("SELECT * FROM cards", callback);
    },
    addCards(newCards, callback){
        return db.query("INSERT INTO cards VALUES(?,?,?,?,?,?)",
        [newCards.idCards, pincode, type, tries, active, creditlimit], callback);
    },
    updateCards(card, callback){
        return db.query("UPDATE cards SET(?,?,?,?,?,?,?) WHERE idCards=?",
        [updateData.idCards, updateData.pincode, updateData.type, updateData.tries, updateData.active, updateData.creditlimit, card], callback);
    },
    deleteCards(card, callback){
        return db.query("DELETE FROM cards WHERE idCards=?",[card], callback);
    }   

}

module.exports = cards;