const db=require('../database');

const user = {
    getAllUser: function(callback){
        return db.query("SELECT * FROM user", callback);
    },
    addUser(newUser, callback){
        return db.query("INSERT INTO user VALUES(?,?,?,?,?,?)",[newUser.idUser,
            newUser.fname,newUser.lname,newUser.address,newUser.phone,newUser.background],callback);
                          
    },
    updateUser(iu,updateData, callback){
        return db.query("UPDATE user SET fname=?, lname=?, address=?, phone=?, background=? WHERE idUser=?",
        [updateData.fname,updateData.lname,updateData.address,updateData.phone,updateData.idUser], [iu], callback);
    },
    deleteUser(iu, callback){
        return db.query("DELETE FROM user WHERE idUser=?", [iu], callback);
    },
    getOneUser(iu, callback){
        return db.query("SELECT * FROM user WHERE idUser=?", [iu], callback);
    }
}
    module.exports=user;