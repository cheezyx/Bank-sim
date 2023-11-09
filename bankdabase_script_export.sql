account_privilegesPRIMARYaccount_privilegesaccount_idaccount_id-- MySQL Script generated by MySQL Workbench
-- Tue Nov  7 20:59:37 2023
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema bankdatabase
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema bankdatabase
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `bankdatabase` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci ;
USE `bankdatabase` ;

-- -----------------------------------------------------
-- Table `bankdatabase`.`accounts`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bankdatabase`.`accounts` (
  `account_id` INT(11) NOT NULL AUTO_INCREMENT,
  `balance` DECIMAL(20,2) NOT NULL DEFAULT '0.00',
  `account_type` ENUM('debit', 'credit') NOT NULL,
  `credit_limit` DECIMAL(20,2) NULL DEFAULT NULL,
  PRIMARY KEY (`account_id`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `bankdatabase`.`customers`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bankdatabase`.`customers` (
  `customer_id` INT(11) NOT NULL AUTO_INCREMENT,
  `first_name` VARCHAR(100) NOT NULL,
  `last_name` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`customer_id`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `bankdatabase`.`account_privileges`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bankdatabase`.`account_privileges` (
  `account_privilege_id` INT(11) NOT NULL AUTO_INCREMENT,
  `account_id` INT(11) NOT NULL,
  `customer_id` INT(11) NOT NULL,
  `access_level` ENUM('owner', 'authorized_user') NOT NULL,
  PRIMARY KEY (`account_privilege_id`),
  INDEX `account_id` (`account_id` ASC) VISIBLE,
  INDEX `customer_id` (`customer_id` ASC) VISIBLE,
  CONSTRAINT `account_privileges_ibfk_1`
    FOREIGN KEY (`account_id`)
    REFERENCES `bankdatabase`.`accounts` (`account_id`)
    ON UPDATE CASCADE,
  CONSTRAINT `account_privileges_ibfk_2`
    FOREIGN KEY (`customer_id`)
    REFERENCES `bankdatabase`.`customers` (`customer_id`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `bankdatabase`.`cards`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bankdatabase`.`cards` (
  `card_id` INT(11) NOT NULL AUTO_INCREMENT,
  `customer_id` INT(11) NOT NULL,
  `card_type` ENUM('debit', 'credit', 'dual') NOT NULL,
  `pin_hashed` VARCHAR(255) NOT NULL,
  PRIMARY KEY (`card_id`),
  INDEX `cards_ibfk_1` (`customer_id` ASC) VISIBLE,
  CONSTRAINT `cards_ibfk1`
    FOREIGN KEY (`customer_id`)
    REFERENCES `bankdatabase`.`customers` (`customer_id`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `bankdatabase`.`card_privileges`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bankdatabase`.`card_privileges` (
  `card_id` INT(11) NOT NULL,
  `account_id` INT(11) NOT NULL,
  PRIMARY KEY (`card_id`, `account_id`),
  INDEX `card_privileges_ibfk_2` (`account_id` ASC) VISIBLE,
  CONSTRAINT `card_privileges_ibfk_1`
    FOREIGN KEY (`card_id`)
    REFERENCES `bankdatabase`.`cards` (`card_id`)
    ON UPDATE CASCADE,
  CONSTRAINT `card_privileges_ibfk_2`
    FOREIGN KEY (`account_id`)
    REFERENCES `bankdatabase`.`accounts` (`account_id`)
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `bankdatabase`.`transactions`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bankdatabase`.`transactions` (
  `transaction_id` INT(11) NOT NULL AUTO_INCREMENT,
  `from_account_id` INT(11) NULL DEFAULT NULL,
  `to_account_id` INT(11) NULL DEFAULT NULL,
  `amount` DECIMAL(20,2) NOT NULL,
  `date_time` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `description` VARCHAR(255) NULL DEFAULT NULL,
  `transaction_type` ENUM('debit_to_debit', 'debit_to_credit', 'credit_to_debit', 'credit_to_credit', 'deposit', 'withdrawal') NULL DEFAULT NULL,
  PRIMARY KEY (`transaction_id`),
  INDEX `transactions_ibfk_1` (`from_account_id` ASC) VISIBLE,
  INDEX `transactions_ibfk_2` (`to_account_id` ASC) VISIBLE,
  CONSTRAINT `transactions_ibfk_1`
    FOREIGN KEY (`from_account_id`)
    REFERENCES `bankdatabase`.`accounts` (`account_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `transactions_ibfk_2`
    FOREIGN KEY (`to_account_id`)
    REFERENCES `bankdatabase`.`accounts` (`account_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
