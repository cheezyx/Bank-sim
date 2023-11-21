DELIMITER //

CREATE PROCEDURE `GetLastFiveTransactions`(IN account_id INT)
BEGIN
    SELECT * FROM transactions 
    WHERE from_account_id = account_id OR to_account_id = account_id 
    ORDER BY date_time DESC 
    LIMIT 5;
END //

DELIMITER ;