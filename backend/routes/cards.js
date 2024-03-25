const express = require('express');
const router = express.Router();
const cards = require('../models/cards_model');

router.get('/',function(request, response){
    logs.getAllCards(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.post('/',function(request, response){
    logs.addCards(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.put('/',function(request, response){
    logs.updateCards(request.params.cardid, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.delete('/',function(request, response){
    logs.deleteCards(request.params.cardid, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

module.exports = router;