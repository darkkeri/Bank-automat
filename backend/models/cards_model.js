const db = require('../database');
const bcryptjs=req('bcryptjs');

const cards = {
    getAllCards(callback){
        return db.query("SELECT * FROM cards", callback);
    },
    addCards(newCards, callback){
        return db.query("INSERT INTO cards VALUES(?,?,?,?,?,?)",
        [idCards, pincode, type, tries, active, creditlimit], callback);
    },
    updateCards(id, callback){
        return db.query("UPDATE cards SET(?,?,?,?,?,?) WHERE idCards=?",
        [idCards, pincode, type, tries, active, creditlimit], callback);
    },
    deleteCards(idCards, callback){
        return db.query("DELETE FROM cards WHERE idCards=?",[idCards], callback);
    }   

}

module.exports = cards;