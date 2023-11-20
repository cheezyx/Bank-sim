const express = require('express');
const router = express.Router();
const transactionsmodel = require('../models/transactions_model');


router.post('/transfer', function (req, res) {
    const { from_account_id, to_account_id, amount, description, transaction_type } = req.body;
    transactionsmodel.transferBalance(from_account_id, to_account_id, amount, description, transaction_type, function(err, result) {
        if (err) {
            res.status(500).json(err);
        } else {
            res.json(result);
        }
    });
});


router.post('/deposit', function (req, res) {
    const { account_id, amount, description } = req.body;
    transactionsmodel.deposit(account_id, amount, description, function(err, result) {
        if (err) {
            res.status(500).json(err);
        } else {
            res.json(result);
        }
    });
});

router.post('/withdraw', function (req, res) {
    const { account_id, amount, description } = req.body;
    transactionsmodel.withdraw(account_id, amount, description, function(err, result) {
        if (err) {
            res.status(500).json(err);
        } else {
            res.json(result);
        }
    });
});

module.exports = router;