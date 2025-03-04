class Book {
    constructor(title, author, isbn) {
        this.title = title;
        this.author = author;
        this.isbn = isbn;
    }
}

class BookManager {
    constructor() {
        this.books = [];
    }

    addBook(book) {
        this.books.push(book);
    }

    removeBook(isbn) {
        this.books = this.books.filter(book => book.isbn !== isbn);
    }

    getBook(isbn) {
        return this.books.find(book => book.isbn === isbn);
    }

    listBooks() {
        return this.books;
    }
}

// Example usage:
const bookManager = new BookManager();

const book1 = new Book('The Great Gatsby', 'F. Scott Fitzgerald', '123456789');
const book2 = new Book('To Kill a Mockingbird', 'Harper Lee', '987654321');

bookManager.addBook(book1);
bookManager.addBook(book2);

console.log(bookManager.listBooks());

bookManager.removeBook('123456789');

console.log(bookManager.listBooks());