const express = require('express');
const router = express.Router();
const account = require('../models/cards_model');

router.get('/:idCards', function(request, response){
    cards.getCardtype(request.params.idCards, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result[0]);
        }
    });
});

module.exports = router;