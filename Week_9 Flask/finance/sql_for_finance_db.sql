CREATE TABLE transaction_history
(
id INTEGER NOT NULL,
cash NUMERIC NOT NULL,
share_name TEXT NOT NULL,
share_quantity_change INTEGER NOT NULL,
cumulative_stock_quantity INTEGER NOT NULL,
transaction_number INTEGER PRIMARY KEY AUTOINCREMENT,
transaction_date TEXT NOT NULL,
FOREIGN KEY (id) REFERENCES users(id)
);

CREATE TABLE stock_portfolio
(
id INTEGER NOT NULL,
stock_name TEXT NOT NULL,
stock_quantity INTEGER NOT NULL,
price_per_stock NUMERIC NOT NULL,
total_price_of_all_stock NUMERIC NOT NULL,
FOREIGN KEY (id) REFERENCES users(id)
);

CREATE TABLE users (
id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
username TEXT NOT NULL,
hash TEXT NOT NULL,
cash NUMERIC NOT NULL DEFAULT 10000.00);


CREATE TABLE sqlite_sequence(name,seq);
CREATE UNIQUE INDEX username ON users (username);

--Total worth =  total_price_of_all_stock plus financial_balance

-- Set trigger here potentially to update total price of all stock
-- on basis of sale, purchase or price change