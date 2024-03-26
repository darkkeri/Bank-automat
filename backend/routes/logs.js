const express = require('express');
const router = express.Router();
const logs = require('../models/logs_model');

router.get('/',function(request, response){
    logs.getAllLogs(function(err, result){
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
    logs.addLogs(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.put('/:logsid', function(request, response){
    logs.updateLogs(request.params.logsid, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.delete('/:logsid', function(request, response){
    logs.deleteLogs(request.params.logsid, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

module.exports = router;
