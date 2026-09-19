let products = [];

document.addEventListener("DOMContentLoaded", function () {

    const productGrid = document.getElementById("productGrid");
    const searchInput = document.getElementById("searchInput");
    const searchButton = document.getElementById("searchButton");
    const categoryButtons =
        document.querySelectorAll(".category-list button");


    function getCart() {

        return JSON.parse(
            localStorage.getItem("arshuMartCart")
        ) || [];

    }


    function saveCart(cart) {

        localStorage.setItem(
            "arshuMartCart",
            JSON.stringify(cart)
        );

    }


    function addToCart(productId) {

        const cart = getCart();

        const existingProduct = cart.find(
            item => item.id === productId
        );

        const product = products.find(
            item => item.id === productId
        );

        if (!product) {
            return;
        }

        if (product.stock <= 0) {
            alert("This product is out of stock.");
            return;
        }

        if (existingProduct) {

            existingProduct.quantity += 1;

        } else {

            cart.push({
                ...product,
                quantity: 1
            });

        }

        saveCart(cart);

        alert("Product added to cart!");

    }


    function displayProducts(productList) {

        if (!productGrid) {
            return;
        }

        productGrid.innerHTML = "";


        if (productList.length === 0) {

            productGrid.innerHTML = `
                <div class="no-products">
                    <h3>No products found</h3>
                    <p>Try a different product name or category.</p>
                </div>
            `;

            return;

        }


        productList.forEach(function (product) {

            const productCard =
                document.createElement("div");

            productCard.className = "product-card";


            const imageHTML = product.image
                ? `
                    <img
                        src="${product.image}"
                        alt="${product.name}"
                        loading="lazy"
                    >
                `
                : `
                    <div class="no-image">
                        Product Image
                    </div>
                `;


            productCard.innerHTML = `

                <div class="product-image">

                    ${imageHTML}

                </div>


                <div class="product-info">

                    <span class="product-category">
                        ${product.category}
                    </span>


                    <h3>
                        ${product.name}
                    </h3>


                    <p>
                        ${product.description || ""}
                    </p>


                    <div class="product-bottom">

                        <strong>
                            ₹${Number(product.price).toLocaleString("en-IN")}
                        </strong>


                        <button
                            type="button"
                            class="add-cart-button"
                            data-product-id="${product.id}"
                            ${product.stock <= 0 ? "disabled" : ""}
                        >
                            ${
                                product.stock <= 0
                                    ? "Out of Stock"
                                    : "Add to Cart"
                            }
                        </button>

                    </div>

                </div>

            `;


            productGrid.appendChild(productCard);

        });


        const addCartButtons =
            document.querySelectorAll(".add-cart-button");


        addCartButtons.forEach(function (button) {

            button.addEventListener(
                "click",
                function () {

                    const productId =
                        Number(button.dataset.productId);

                    addToCart(productId);

                }
            );

        });

    }


    function searchProducts() {

        const searchText =
            searchInput.value.trim().toLowerCase();


        const filteredProducts =
            products.filter(function (product) {

                return (

                    product.name
                        .toLowerCase()
                        .includes(searchText)

                    ||

                    product.category
                        .toLowerCase()
                        .includes(searchText)

                    ||

                    (product.description || "")
                        .toLowerCase()
                        .includes(searchText)

                );

            });


        displayProducts(filteredProducts);

    }


    function filterByCategory(category) {

        if (category === "All") {

            displayProducts(products);

            return;

        }


        const filteredProducts =
            products.filter(function (product) {

                return product.category === category;

            });


        displayProducts(filteredProducts);

    }


    async function loadProducts() {

        try {

            const response =
                await fetch(
                    "http://127.0.0.1:8080/api/products"
                );


            if (!response.ok) {

                throw new Error(
                    "Server response failed"
                );

            }


            const data =
                await response.json();


            if (!data.success) {

                throw new Error(
                    data.message || "Unable to load products"
                );

            }


            products = data.products;


            console.log(
                "Products loaded from database:",
                products.length
            );


            displayProducts(products);

        }

        catch (error) {

            console.error(
                "Product loading error:",
                error
            );


            if (productGrid) {

                productGrid.innerHTML = `
                    <div class="no-products">

                        <h3>
                            Unable to load products
                        </h3>

                        <p>
                            Please make sure the ArshuMart backend is running.
                        </p>

                    </div>
                `;

            }

        }

    }


    if (productGrid) {

        if (searchButton) {

            searchButton.addEventListener(
                "click",
                searchProducts
            );

        }


        if (searchInput) {

            searchInput.addEventListener(
                "keydown",
                function (event) {

                    if (event.key === "Enter") {

                        searchProducts();

                    }

                }
            );

        }


        categoryButtons.forEach(function (button) {

            button.addEventListener(
                "click",
                function () {

                    const category =
                        button.textContent.trim();

                    filterByCategory(category);

                }
            );

        });


        loadProducts();

    }

});