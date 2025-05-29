import pandas as pd
df = pd.read_csv('data/raw/Amazon_Sale_Report.csv', low_memory=False)

#drop unnecessary columns
if 'Unnamed: 22' in df.columns:
    df.drop(columns=['Unnamed: 22'], inplace=True)
if 'index' in df.columns:
    df.drop(columns=['index'], inplace=True)

df.columns = df.columns.str.strip().str.lower().str.replace(' ' , '_', regex=True).str.replace('-', '_', regex=True)

# Convert types
df['date'] = pd.to_datetime(df['date'], format='%m-%d-%y', errors='coerce')

df['qty'] = pd.to_numeric(df['qty'], errors='coerce').fillna(0).astype(int)
df['amount'] = pd.to_numeric(df['amount'], errors='coerce').fillna(0)

df['ship_postal_code'] = df['ship_postal_code'].fillna('').astype(str)
df['b2b'] = df['b2b'].astype(bool)

for col in ['status', 'fulfilment', 'sales_channel', 'ship_service_level', 'currency', 'fulfilled_by', 'courier_status']:
    df[col] = df[col].astype('category')

# Handle missing critical values
df.dropna(subset=['order_id', 'sku', 'date', 'amount'], inplace=True)

# Fill missing 'fulfilled_by'
df['fulfilled_by'] = df['fulfilled_by'].cat.add_categories(['Unknown']).fillna('Unknown')

print(df.head())
print(df.info())

# seperate dataframes
orders_df = df[[
    'order_id', 'date', 'status', 'sales_channel', 'amount', 'promotion_ids', 'b2b'
]].drop_duplicates()

products_df = df[[
    'sku', 'style', 'category', 'size', 'asin', 'currency'
]].drop_duplicates()

order_items_df = df[[
    'order_id', 'sku', 'qty', 'fulfilment', 'fulfilled_by'
]]

shipping_df = df[[
    'order_id', 'ship_service_level', 'courier_status',
    'ship_city', 'ship_state', 'ship_postal_code', 'ship_country'
]].drop_duplicates(subset=['order_id'])

products_df.to_csv('data/clean/products.csv', index=False)
orders_df.to_csv('data/clean/orders.csv', index=False)
shipping_df.to_csv('data/clean/shipping.csv', index=False)
order_items_df.to_csv('data/clean/order_items.csv', index=False)

