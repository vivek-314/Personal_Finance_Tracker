let editingId = null;

const ctx = document.getElementById("expenseChart").getContext("2d");
let expenseChart = null;

// Load existing transactions or start with an empty array
let transactions = JSON.parse(localStorage.getItem("transactions")) || [];

// Form elements
const form = document.getElementById("transactionForm");
const tableBody = document.getElementById("transactionTable");

const balanceEl = document.getElementById("balance");
const incomeEl = document.getElementById("income");
const expenseEl = document.getElementById("expense");

const searchBox = document.getElementById("searchBox");
const filterType = document.getElementById("filterType");

const submitBtn = document.querySelector("#transactionForm button");

searchBox.addEventListener("input",renderTransactions);

filterType.addEventListener("change",renderTransactions);

// When form is submitted
form.addEventListener("submit", function(e){

    e.preventDefault();

    const transaction = {

        id: Date.now(),

        title: document.getElementById("title").value,

        amount: Number(document.getElementById("amount").value),

        type: document.getElementById("type").value,

        category: document.getElementById("category").value,

        date: document.getElementById("date").value

    };

    if(editingId === null){

        transactions.push(transaction);

    }else{

        transaction.id = editingId;

        transactions = transactions.map(t =>
            t.id === editingId ? transaction : t
    );

        editingId = null;

    }

    saveTransactions();

    renderTransactions();

    updateSummary();

    form.reset();

    document.querySelector("#transactionForm button").textContent = "Add Transaction";

});

function saveTransactions(){

    localStorage.setItem(
        "transactions",
        JSON.stringify(transactions)
    );

}

function renderTransactions() {

    tableBody.innerHTML = "";

    if(transactions.length===0){

    tableBody.innerHTML=`
        <tr>
            <td colspan="6">
                No transactions yet.
            </td>
        </tr>
    `;

    return;
}

    const keyword = searchBox.value.toLowerCase();
    const filter = filterType.value;

    transactions
        .filter(transaction => {

            const matchSearch =
                transaction.title.toLowerCase().includes(keyword) ||
                transaction.category.toLowerCase().includes(keyword);

            const matchFilter =
                filter === "all" ||
                transaction.type === filter;

            return matchSearch && matchFilter;

        })
        .forEach(transaction => {

            const row = document.createElement("tr");

            row.innerHTML = `
                <td>${transaction.date}</td>
                <td>
                    ${transaction.type==="income"
                    ?'<span class="badge-income">Income</span>'
                    :'<span class="badge-expense">Expense</span>'}
                </td>

                <td>${transaction.category}</td>
                <td>${transaction.type}</td>
                <td>₹${transaction.amount}</td>
                <td>
                        <button class="edit-btn" onclick="editTransaction(${transaction.id})">Edit Transaction✏️</button>
                        <button class="delete-btn" onclick="deleteTransaction(${transaction.id})">Delete Transaction🗑️</button>
                </td>
            `;

            tableBody.appendChild(row);

        });

}

function updateSummary(){

    let income = 0;

    let expense = 0;

    transactions.forEach(transaction=>{

        if(transaction.type==="income")

            income += transaction.amount;

        else

            expense += transaction.amount;

    });

    balanceEl.innerText = `₹${(income-expense).toLocaleString("en-IN")}`;

    incomeEl.innerText = `₹${income.toLocaleString("en-IN")}`;

    expenseEl.innerText = `₹${expense.toLocaleString("en-IN")}`;

}

function deleteTransaction(id){

    if(!confirm("Delete this transaction?"))
        return;

    transactions = transactions.filter(
        transaction => transaction.id !== id
    );

    saveTransactions();
    renderTransactions();
    updateSummary();
}

function updateChart(){

    const categoryTotals = {};

    transactions.forEach(transaction => {

        if(transaction.type === "expense"){

            if(categoryTotals[transaction.category]){

                categoryTotals[transaction.category] += transaction.amount;

            }else{

                categoryTotals[transaction.category] = transaction.amount;

            }

        }

    });

    const labels = Object.keys(categoryTotals);

    const data = Object.values(categoryTotals);

    if(expenseChart){

        expenseChart.destroy();

    }

    expenseChart = new Chart(ctx, {

        type: "pie",

        data:{

            labels: labels,

            datasets:[{

                data:data

            }]

        },

        options:{

            responsive:true,

                maintainAspectRatio:false,

            plugins:{

                    legend:{

                    position:"bottom",

                        labels:{

                            font:{
                            size:16,
                            weight:"bold"
                            },

                            padding:20

                        }

                    }

                }

        }

    });

}








document.getElementById("exportBtn").addEventListener("click", exportCSV);

function exportCSV(){

    let csv = "Date,Title,Category,Type,Amount\n";

    transactions.forEach(t => {

        csv += `${t.date},${t.title},${t.category},${t.type},${t.amount}\n`;

    });

    const blob = new Blob([csv], {type: "text/csv"});

    const url = window.URL.createObjectURL(blob);

    const a = document.createElement("a");

    a.href = url;

    a.download = "transactions.csv";

    a.click();

    window.URL.revokeObjectURL(url);

}

function editTransaction(id){

    const t = transactions.find(x => x.id === id);
    

    document.getElementById("title").value = t.title;

    document.getElementById("amount").value = t.amount;

    document.getElementById("type").value = t.type;

    document.getElementById("category").value = t.category;

    document.getElementById("date").valueAsDate = new Date();

    editingId = id;

    submitBtn.textContent = "Update Transaction";

}

renderTransactions();
expenseEl.innerText = "₹" + expense;

updateSummary();

updateChart();