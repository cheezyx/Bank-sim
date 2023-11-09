const express = require('express');
const router = express.Router();
const transactions = require('../models/transactions_model');

router.get('/', function (request, response) {
    transactions.getAll(function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    });
});

router.get('/:id', function (request, response) {
    transactions.getById(request.params.id, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult[0]);
        }
    });
});

router.post('/', function(request, response) {
    transactions.add(request.body, function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(request.body); // You might want to return the created object here
        }
    });
});

router.delete('/:id', function(request, response) {
    transactions.delete(request.params.id, function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    });
});

router.put('/:id', function(request, response) {
    transactions.update(request.params.id, request.body, function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    });
});

module.exports = router;