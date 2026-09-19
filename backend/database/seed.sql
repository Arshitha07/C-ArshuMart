PRAGMA foreign_keys = ON;

-- =========================================================
-- ARSHUMART SEED DATA
-- =========================================================

-- -------------------------
-- USERS
-- -------------------------

INSERT OR IGNORE INTO users
(name, email, password_hash, role)
VALUES
('ArshuMart Seller', 'seller@arshumart.com', 'seller123', 'seller');

INSERT OR IGNORE INTO users
(name, email, password_hash, role)
VALUES
('ArshuMart Admin', 'admin@arshumart.com', 'admin123', 'admin');


-- =========================================================
-- ELECTRONICS
-- =========================================================

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'NovaSound Wireless Headphones',
       'Premium wireless headphones with deep bass and clear audio.',
       'Electronics',
       1499,
       50,
       'https://images.unsplash.com/photo-1505740420928-5e560c06d30e?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'NovaSound Wireless Headphones'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'PulseFit Smart Watch',
       'Smart fitness watch with activity tracking and modern display.',
       'Electronics',
       2499,
       40,
       'https://images.unsplash.com/photo-1523275335684-37898b6baf30?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'PulseFit Smart Watch'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'VoltEdge Power Bank',
       'Portable fast-charging power bank for everyday travel.',
       'Electronics',
       1299,
       60,
       'https://images.unsplash.com/photo-1609592424950-6f9f4b0b7b5d?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'VoltEdge Power Bank'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'ClearView Bluetooth Speaker',
       'Compact Bluetooth speaker designed for powerful room-filling sound.',
       'Electronics',
       999,
       45,
       'https://images.unsplash.com/photo-1608043152269-423dbba4e7e1?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'ClearView Bluetooth Speaker'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'SmartGlow LED Desk Lamp',
       'Adjustable LED desk lamp for study and workspace lighting.',
       'Electronics',
       799,
       35,
       'https://images.unsplash.com/photo-1507473885765-e6ed057f782c?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'SmartGlow LED Desk Lamp'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'KeyNova Mechanical Keyboard',
       'Responsive mechanical keyboard for work, study and gaming.',
       'Electronics',
       1899,
       30,
       'https://images.unsplash.com/photo-1587829741301-dc798b83add3?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'KeyNova Mechanical Keyboard'
);


-- =========================================================
-- FASHION
-- =========================================================

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'UrbanPro Everyday Backpack',
       'Durable backpack designed for college, office and travel.',
       'Fashion',
       899,
       50,
       'https://images.unsplash.com/photo-1553062407-98eeb64c6a62?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'UrbanPro Everyday Backpack'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'ClassicFit Cotton Shirt',
       'Comfortable casual cotton shirt for everyday wear.',
       'Fashion',
       699,
       70,
       'https://images.unsplash.com/photo-1521572163474-6864f9cf17ab?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'ClassicFit Cotton Shirt'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'StreetStyle Denim Jeans',
       'Comfortable everyday denim jeans with a modern fit.',
       'Fashion',
       1199,
       45,
       'https://images.unsplash.com/photo-1542272604-787c3835535d?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'StreetStyle Denim Jeans'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'ComfortWalk Casual Shoes',
       'Lightweight casual shoes designed for daily walking.',
       'Fashion',
       1499,
       40,
       'https://images.unsplash.com/photo-1549298916-b41d501d3772?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'ComfortWalk Casual Shoes'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'UrbanEdge Casual T-Shirt',
       'Soft everyday round-neck T-shirt with a simple modern style.',
       'Fashion',
       499,
       80,
       'https://images.unsplash.com/photo-1503342217505-b0a15ec3261c?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'UrbanEdge Casual T-Shirt'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'AeroLine Travel Jacket',
       'Lightweight everyday jacket suitable for travel and outdoor use.',
       'Fashion',
       1799,
       35,
       'https://images.unsplash.com/photo-1551028719-00167b16eac5?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'AeroLine Travel Jacket'
);


-- =========================================================
-- BEAUTY & PERSONAL CARE
-- =========================================================

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'GlowCare Face Wash',
       'Gentle daily face cleansing formula.',
       'Beauty & Personal Care',
       349,
       60,
       'https://images.unsplash.com/photo-1556228578-8c89e6adf883?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'GlowCare Face Wash'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'SilkRoot Herbal Shampoo',
       'Refreshing shampoo designed for everyday hair care.',
       'Beauty & Personal Care',
       499,
       55,
       'https://images.unsplash.com/photo-1620916566398-39f1143ab7be?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'SilkRoot Herbal Shampoo'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'PureGlow Face Moisturizer',
       'Lightweight daily moisturizing cream.',
       'Beauty & Personal Care',
       399,
       50,
       'https://images.unsplash.com/photo-1611930022073-b7a4ba5fcccd?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'PureGlow Face Moisturizer'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'FreshMist Body Wash',
       'Refreshing body wash for daily use.',
       'Beauty & Personal Care',
       299,
       65,
       'https://images.unsplash.com/photo-1608248543803-ba4f8c70ae0b?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'FreshMist Body Wash'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'SoftTouch Hand Cream',
       'Nourishing hand cream for everyday care.',
       'Beauty & Personal Care',
       249,
       70,
       'https://images.unsplash.com/photo-1601055903647-ddf1ee9701c7?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'SoftTouch Hand Cream'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'VelvetBloom Lip Care',
       'Smooth lip care balm for everyday use.',
       'Beauty & Personal Care',
       199,
       75,
       'https://images.unsplash.com/photo-1586495777744-4413f21062fa?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'VelvetBloom Lip Care'
);


-- =========================================================
-- HOME & KITCHEN
-- =========================================================

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'HomeNest Storage Organizer',
       'Practical organizer for everyday household storage.',
       'Home & Kitchen',
       699,
       40,
       'https://images.unsplash.com/photo-1618221195710-dd6b41faaea6?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'HomeNest Storage Organizer'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'ChefMate Non-Stick Pan',
       'Easy cooking pan with durable non-stick coating.',
       'Home & Kitchen',
       899,
       35,
       'https://images.unsplash.com/photo-1556911220-e15b29be8c8f?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'ChefMate Non-Stick Pan'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'KitchenPro Knife Set',
       'Essential kitchen knives for everyday cooking.',
       'Home & Kitchen',
       799,
       30,
       'https://images.unsplash.com/photo-1593618998160-e34014e67546?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'KitchenPro Knife Set'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'HomeEase Water Bottle',
       'Reusable bottle designed for home, college and travel.',
       'Home & Kitchen',
       349,
       70,
       'https://images.unsplash.com/photo-1602143407151-7111542de6e8?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'HomeEase Water Bottle'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'CleanNest Storage Box',
       'Multipurpose storage box for home organization.',
       'Home & Kitchen',
       499,
       50,
       'https://images.unsplash.com/photo-1586023492125-27b2c045efd7?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'CleanNest Storage Box'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'BrewCraft Coffee Maker',
       'Compact coffee maker for convenient home brewing.',
       'Home & Kitchen',
       2299,
       25,
       'https://images.unsplash.com/photo-1517668808822-9ebb02f2a0e6?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'BrewCraft Coffee Maker'
);


-- =========================================================
-- BOOKS
-- =========================================================

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'The Curious Mind',
       'An inspiring book about curiosity, learning and creativity.',
       'Books',
       399,
       40,
       'https://images.unsplash.com/photo-1543002588-bfa74002ed7e?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'The Curious Mind'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'Journey Through Stories',
       'A collection of engaging stories for relaxed reading.',
       'Books',
       449,
       35,
       'https://images.unsplash.com/photo-1512820790803-83ca734da794?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'Journey Through Stories'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'C++ Coding Essentials',
       'Beginner-friendly programming reference for C++ learners.',
       'Books',
       599,
       30,
       'https://images.unsplash.com/photo-1532012197267-da84d127e765?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'C++ Coding Essentials'
);


-- =========================================================
-- SPORTS
-- =========================================================

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'FlexCore Yoga Mat',
       'Comfortable exercise mat for yoga and home workouts.',
       'Sports',
       799,
       45,
       'https://images.unsplash.com/photo-1601925260368-ae2f83cf8b7f?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'FlexCore Yoga Mat'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'SprintMax Sports Bottle',
       'Lightweight sports bottle for workouts and outdoor activities.',
       'Sports',
       399,
       60,
       'https://images.unsplash.com/photo-1523362628745-0c100150b504?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'SprintMax Sports Bottle'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'ProStrike Football',
       'Durable football designed for recreational outdoor play.',
       'Sports',
       699,
       40,
       'https://images.unsplash.com/photo-1579952363873-27f3bade9f55?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'ProStrike Football'
);


-- =========================================================
-- TOYS
-- =========================================================

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'BuildMaster Construction Set',
       'Creative building set designed for imaginative play.',
       'Toys',
       699,
       35,
       'https://images.unsplash.com/photo-1587654780291-39c9404d746b?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'BuildMaster Construction Set'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'RoboBuddy Learning Robot',
       'Interactive educational robot toy for creative learning.',
       'Toys',
       1599,
       25,
       'https://images.unsplash.com/photo-1485827404703-89b55fcc595e?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'RoboBuddy Learning Robot'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'MiniRacer Remote Car',
       'Compact remote-controlled racing car for indoor and outdoor play.',
       'Toys',
       999,
       30,
       'https://images.unsplash.com/photo-1594787318286-3d835c1d207f?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'MiniRacer Remote Car'
);


-- =========================================================
-- GROCERIES
-- =========================================================

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'GoldenHarvest Basmati Rice',
       'Premium long-grain rice for everyday family meals.',
       'Groceries',
       899,
       50,
       'https://images.unsplash.com/photo-1586201375761-83865001e31c?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'GoldenHarvest Basmati Rice'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'MorningBrew Ground Coffee',
       'Aromatic ground coffee for a fresh morning brew.',
       'Groceries',
       449,
       45,
       'https://images.unsplash.com/photo-1495474472287-4d71bcdd2085?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'MorningBrew Ground Coffee'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'NatureCrunch Mixed Nuts',
       'Crunchy mixed nuts packed for convenient snacking.',
       'Groceries',
       599,
       40,
       'https://images.unsplash.com/photo-1599599810694-b5ac3c7b6c9c?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'NatureCrunch Mixed Nuts'
);


-- =========================================================
-- ACCESSORIES
-- =========================================================

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'TimeCraft Classic Watch',
       'Minimal everyday watch with a clean classic design.',
       'Accessories',
       1299,
       30,
       'https://images.unsplash.com/photo-1524805444758-089113d48a6d?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'TimeCraft Classic Watch'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'VisionEdge Sunglasses',
       'Modern sunglasses with a lightweight everyday frame.',
       'Accessories',
       899,
       45,
       'https://images.unsplash.com/photo-1511499767150-a48a237f0083?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'VisionEdge Sunglasses'
);

INSERT INTO products
(seller_id, name, description, category, price, stock, image_url)
SELECT id,
       'CarryLite Wallet',
       'Compact everyday wallet with multiple card slots.',
       'Accessories',
       499,
       50,
       'https://images.unsplash.com/photo-1627123424574-724758594e93?auto=format&fit=crop&w=800&q=80'
FROM users
WHERE email = 'seller@arshumart.com'
AND NOT EXISTS (
    SELECT 1 FROM products WHERE name = 'CarryLite Wallet'
);