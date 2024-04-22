const express = require('express');
const router = express.Router();
const account = require('../models/account_model');

router.get('/', function(request, response){
        account.getAccountByType(request.body.idCards,request.body.accounttype, function(err, result){
            if(err){
                console.log(err.errno);
                response.json(err.errno);
            }
            else{
                console.log("Kortti ok");
                response.send(result);
            }
        });
});


module.exports = router;