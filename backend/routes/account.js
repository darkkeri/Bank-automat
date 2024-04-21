const express = require('express');
const router = express.Router();
const account = require('../models/account_model');

router.get('/',function(request, response){
    account.getAllAccount(function(err, result){
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
    account.addAccount(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.put('/:accountN', function(request, response){
    account.updateAccount(request.params.accountN, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.delete('/:accountN', function(request, response){
    account.deleteAccount(request.params.accountN, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});


router.get('/:accountN', function(request, response){
    account.getOneAccount(request.params.accountN, function(err, result){
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