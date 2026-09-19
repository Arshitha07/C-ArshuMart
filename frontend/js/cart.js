/* =========================================================
   ArshuMart CART SYSTEM
   ========================================================= */


/* =========================
   GET CART
   ========================= */

function getCart() {

    try {

        return JSON.parse(
            localStorage.getItem("cart")
        ) || [];

    } catch (error) {

        console.error(
            "Cart data error:",
            error
        );

        return [];

    }

}


/* =========================
   SAVE CART
   ========================= */

function saveCart(cart) {

    localStorage.setItem(
        "cart",
        JSON.stringify(cart)
    );

}


/* =========================
   UPDATE CART COUNT
   ========================= */

function updateCartCount() {

    const cart = getCart();

    const totalItems = cart.reduce(
        (total, item) => {

            return total +
                Number(item.quantity || 0);

        },
        0
    );


    const cartCount =
        document.getElementById(
            "cartCount"
        );

    const summaryCount =
        document.getElementById(
            "summaryCount"
        );


    if (cartCount) {

        cartCount.textContent =
            `${totalItems} ${
                totalItems === 1
                    ? "item"
                    : "items"
            }`;

    }


    if (summaryCount) {

        summaryCount.textContent =
            totalItems;

    }

}


/* =========================
   UPDATE TOTAL
   ========================= */

function updateCartTotal() {

    const cart = getCart();

    const total = cart.reduce(
        (sum, item) => {

            const price =
                Number(item.price || 0);

            const quantity =
                Number(item.quantity || 0);

            return sum +
                (price * quantity);

        },
        0
    );


    const cartTotal =
        document.getElementById(
            "cartTotal"
        );


    if (cartTotal) {

        cartTotal.textContent =
            `₹${total.toLocaleString(
                "en-IN",
                {
                    minimumFractionDigits: 2,
                    maximumFractionDigits: 2
                }
            )}`;

    }

}


/* =========================
   RENDER CART
   ========================= */

function renderCart() {

    const cart =
        getCart();

    const cartItems =
        document.getElementById(
            "cartItems"
        );


    if (!cartItems) {

        return;

    }


    /* =====================
       EMPTY CART
       ===================== */

    if (cart.length === 0) {

        cartItems.innerHTML = `

            <div class="empty-cart">

                <div class="empty-cart-icon">
                    🛒
                </div>

                <h3>
                    Your cart is empty
                </h3>

                <p>
                    You haven't added any
                    products yet.
                </p>

                <button
                    type="button"
                    onclick="window.location.href='products.html'"
                >
                    Start Shopping
                </button>

            </div>

        `;

        updateCartCount();
        updateCartTotal();

        return;

    }


    /* =====================
       SHOW PRODUCTS
       ===================== */

    cartItems.innerHTML =
        cart.map(
            (item, index) => {

                const productId =
                    Number(
                        item.productId ||
                        item.id
                    );

                const name =
                    item.name ||
                    "Product";

                const price =
                    Number(
                        item.price || 0
                    );

                const quantity =
                    Math.max(
                        1,
                        Number(
                            item.quantity || 1
                        )
                    );

                const image =
                    item.image ||
                    `https://picsum.photos/seed/arshumart-cart-${productId}/500/500`;

                const itemTotal =
                    price * quantity;


                return `

                    <div
                        class="cart-item"
                        data-product-id="${productId}"
                    >

                        <!-- PRODUCT IMAGE -->

                        <div class="cart-item-image">

                            <img
                                src="${image}"
                                alt="${name}"

                                onerror="
                                    this.onerror=null;
                                    this.src='https://picsum.photos/seed/arshumart-cart-${productId}/500/500';
                                "
                            >

                        </div>


                        <!-- PRODUCT DETAILS -->

                        <div class="cart-item-details">

                            <h3>
                                ${name}
                            </h3>

                            <p class="cart-item-price">
                                ₹${price.toLocaleString(
                                    "en-IN",
                                    {
                                        minimumFractionDigits: 2,
                                        maximumFractionDigits: 2
                                    }
                                )}
                            </p>


                            <!-- QUANTITY -->

                            <div class="quantity-control">

                                <button
                                    type="button"
                                    onclick="decreaseQuantity(${productId})"
                                >
                                    −
                                </button>

                                <span>
                                    ${quantity}
                                </span>

                                <button
                                    type="button"
                                    onclick="increaseQuantity(${productId})"
                                >
                                    +
                                </button>

                            </div>


                            <button
                                type="button"
                                class="remove-cart-item"
                                onclick="removeFromCart(${productId})"
                            >
                                Remove
                            </button>

                        </div>


                        <!-- ITEM TOTAL -->

                        <div class="cart-item-total">

                            ₹${itemTotal.toLocaleString(
                                "en-IN",
                                {
                                    minimumFractionDigits: 2,
                                    maximumFractionDigits: 2
                                }
                            )}

                        </div>

                    </div>

                `;

            }
        ).join("");


    updateCartCount();

    updateCartTotal();

}


/* =========================
   INCREASE QUANTITY
   ========================= */

function increaseQuantity(
    productId
) {

    const cart =
        getCart();


    const item =
        cart.find(
            product =>
                Number(
                    product.productId ||
                    product.id
                ) === Number(productId)
        );


    if (!item) {

        return;

    }


    item.quantity =
        Number(
            item.quantity || 1
        ) + 1;


    saveCart(cart);

    renderCart();

}


/* =========================
   DECREASE QUANTITY
   ========================= */

function decreaseQuantity(
    productId
) {

    const cart =
        getCart();


    const item =
        cart.find(
            product =>
                Number(
                    product.productId ||
                    product.id
                ) === Number(productId)
        );


    if (!item) {

        return;

    }


    const currentQuantity =
        Number(
            item.quantity || 1
        );


    if (currentQuantity <= 1) {

        removeFromCart(
            productId
        );

        return;

    }


    item.quantity =
        currentQuantity - 1;


    saveCart(cart);

    renderCart();

}


/* =========================
   REMOVE PRODUCT
   ========================= */

function removeFromCart(
    productId
) {

    let cart =
        getCart();


    cart =
        cart.filter(
            item =>
                Number(
                    item.productId ||
                    item.id
                ) !== Number(productId)
        );


    saveCart(cart);

    renderCart();

}


/* =========================
   CHECKOUT
   ========================= */

function proceedToCheckout() {

    const cart =
        getCart();


    if (!cart.length) {

        alert(
            "Your cart is empty."
        );

        return;

    }


    const userData =
        JSON.parse(
            localStorage.getItem(
                "arshuMartUser"
            )
        );


    if (!userData || !userData.id) {

        alert(
            "Please login before checkout."
        );

        window.location.href =
            "login.html";

        return;

    }


    const items =
        cart.map(
            item => ({

                productId:
                    Number(
                        item.productId ||
                        item.id
                    ),

                quantity:
                    Number(
                        item.quantity || 1
                    )

            })
        );


    const checkoutButton =
        document.getElementById(
            "checkoutButton"
        );


    if (checkoutButton) {

        checkoutButton.disabled =
            true;

        checkoutButton.textContent =
            "Processing...";

    }


    fetch(
        "http://127.0.0.1:8080/api/checkout",
        {

            method: "POST",

            headers: {
                "Content-Type":
                    "application/json"
            },

            body: JSON.stringify({

                buyerId:
                    Number(
                        userData.id
                    ),

                items:
                    items

            })

        }
    )

    .then(
        response =>
            response.json()
    )

    .then(
        result => {

            if (!result.success) {

                throw new Error(
                    result.message ||
                    "Checkout failed."
                );

            }


            /* =================
               ORDER SUCCESS
               ================= */

            localStorage.removeItem(
                "cart"
            );


            alert(
                "Order placed successfully!"
            );


            window.location.href =
                "orders.html";

        }
    )

    .catch(
        error => {

            console.error(
                "Checkout error:",
                error
            );


            alert(
                error.message ||
                "Unable to place order."
            );


            if (checkoutButton) {

                checkoutButton.disabled =
                    false;

                checkoutButton.textContent =
                    "Proceed to Checkout";

            }

        }
    );

}


/* =========================
   CHECKOUT BUTTON
   ========================= */

const checkoutButton =
    document.getElementById(
        "checkoutButton"
    );


if (checkoutButton) {

    checkoutButton.addEventListener(
        "click",
        proceedToCheckout
    );

}


/* =========================
   INITIAL LOAD
   ========================= */

document.addEventListener(
    "DOMContentLoaded",
    function () {

        renderCart();

    }
);