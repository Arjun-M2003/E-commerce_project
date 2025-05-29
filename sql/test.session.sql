CREATE TABLE orders (
    order_id VARCHAR(30) PRIMARY KEY,
    date DATE,
    status VARCHAR(50),
    sales_channel VARCHAR(50),
    amount FLOAT,
    promotion_ids TEXT,
    b2b BOOLEAN
);

CREATE TABLE products (
    sku VARCHAR(30) PRIMARY KEY,
    style VARCHAR(100),
    category VARCHAR(100),
    size VARCHAR(50),
    asin VARCHAR(30),
    currency VARCHAR(10)
);

CREATE TABLE order_items (
    order_id VARCHAR(30),
    sku VARCHAR(30),
    qty INT,
    fulfilment VARCHAR(50),
    fulfilled_by VARCHAR(50),
    FOREIGN KEY (order_id) REFERENCES orders(order_id),
    FOREIGN KEY (sku) REFERENCES products(sku)
);

CREATE TABLE shipping_info (
    order_id VARCHAR(30) PRIMARY KEY,
    ship_service_level VARCHAR(50),
    courier_status VARCHAR(50),
    ship_city VARCHAR(100),
    ship_state VARCHAR(100),
    ship_postal_code VARCHAR(20),
    ship_country VARCHAR(50),
    FOREIGN KEY (order_id) REFERENCES orders(order_id)
);
