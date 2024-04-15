const express = require('express');
const router = express.Router();
const cards = require('../models/cards_model');

router.post('/',function(request, response){
    cards.login(request.body.cardnumber, function(err,result){
        if(err){

        }
        else{
            console.log(result);
            response.json(result[0].pincode);
        }
    });
});
