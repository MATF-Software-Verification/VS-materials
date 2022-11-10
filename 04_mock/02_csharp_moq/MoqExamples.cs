public interface IBookService
{
    string GetISBNFor(string bookTitle);
    IEnumerable<string> GetBooksForCategory(string categoryId);
}

public interface IEmailSender
{
    public void SendEmail(string to, string subject, string body);
}

public class AccountService
{
    private IBookService _bookService;
    private IEmailSender _emailSender;

    public AccountService(IBookService bookService, IEmailSender emailSender)
    {
        _bookService = bookService;
        _emailSender = emailSender;
    }
    
    public IEnumerable<string> GetAllBooksForCategory(string categoryId)
    {
        var allBooks = _bookService.GetBooksForCategory(categoryId);
        return allBooks;
    }
    
    public string GetBookISBN(string categoryId, string searchTerm)
    {
        var allBooks = _bookService.GetBooksForCategory(categoryId);
        var foundBook = allBooks
            .Where(x => x.ToUpper().Contains(searchTerm.ToUpper()))
            .FirstOrDefault();
        
        if (foundBook is null)
        {
            return string.Empty;
        }

        return _bookService.GetISBNFor(foundBook);
    }

    public void SendEmail(string emailAddress, string bookTitle)
    {
        string subject = "Awesome Book";
        string body = $"Hi,\n\nThis book is awesome: {bookTitle}.\nCheck it out.";
        _emailSender.SendEmail(emailAddress, subject, body);
    }
}

public class SampleAccountServiceTests
{
    [Fact]
    public void GetAllBooksForCategory_returns_list_of_available_books()
    {
        // 1
        var bookServiceStub = new Mock<IBookService>();
        
        // 2
        bookServiceStub
            .Setup(x => x.GetBooksForCategory("UnitTesting"))
            .Returns(new List<string> {
                "The Art of Unit Testing",
                "Test-Driven Development",
                "Working Effectively with Legacy Code"
            });
        
        // 3
        var accountService = new AccountService(bookServiceStub.Object, null);
        IEnumerable<string> result = accountService.GetAllBooksForCategory("UnitTesting");
        
        // 4
        Assert.Equal(3, result.Count());
    }

    [Fact]
    public void GetBookISBN_founds_the_correct_book_for_search_term()
    {
        var bookServiceStub = new Mock<IBookService>();

        // 1
        bookServiceStub
            .Setup(x => x.GetBooksForCategory("UnitTesting"))
            .Returns(new List<string>
            {
                "The Art of Unit Testing",
                "Test-Driven Development",
                "Working Effectively with Legacy Code"
            });

        // 2
        bookServiceStub
            .Setup(x => x.GetISBNFor("The Art of Unit Testing"))
            .Returns("0-9020-7656-6");
        
        // 3
        var accountService = new AccountService(bookServiceStub.Object, null);
        string result = accountService.GetBookISBN("UnitTesting", "art");
        
        // 4
        Assert.Equal("0-9020-7656-6", result);
    }

    [Fact]
    public void GetAllBooksForCategory_returns_list_of_available_books_with_callback()
    {
        var bookServiceStub = new Mock<IBookService>();
        string passedParameter = string.Empty;
        bookServiceStub
            .Setup(x => x.GetBooksForCategory(It.IsAny<string>()))
            .Callback<string>(s => passedParameter = s)
            .Returns(new List<string>
            {
                "The Art of Unit Testing",
                "Test-Driven Development",
                "Working Effectively with Legacy Code"
            });
        var accountService = new AccountService(bookServiceStub.Object, null);
        IEnumerable<string> result = accountService.GetAllBooksForCategory("UnitTesting");
        Assert.Equal("UnitTesting", passedParameter);
    }

    [Fact]
    public void SendEmail_sends_email_with_correct_content()
    {
        // 1
        var emailSenderMock = new Mock<IEmailSender>();
        
        // 2
        var accountService = new AccountService(null, emailSenderMock.Object);
        // 3
        
        accountService.SendEmail("test@gmail.com", "Test - Driven Development");
        // 4
        emailSenderMock.Verify(
            x => x.SendEmail(
                "test@gmail.com", 
                "Awesome Book", 
                $"Hi,\n\nThis book is awesome: Test - Driven Development.\nCheck it out."
            ),
            Times.Once
        );
    }

    public void MoreExamples()
    {
        var bookServiceStub = new Mock<IBookService>();

        bookServiceStub
            .SetupSequence(x => x.GetISBNFor(It.IsAny<string>()))
            .Returns("0-9020-7656-6") //returned on 1st call
            .Returns("0-9180-6396-5") //returned on 2nd call
            .Returns("0-3860-1173-7") //returned on 3rd call
            .Returns("0-5570-1450-6");//returned on 4th call
        
        bookServiceStub
            .Setup(x => x.GetBooksForCategory(It.IsAny<string>()))
            .Throws<InvalidOperationException>();

        emailSenderMock.Setup(x => x.EmailServer).Returns("Gmail");
        bookServiceStub.SetupAllProperties();
    }

    public void AsyncExamples()
    {
        httpClientMock
            .Setup(x => x.GetAsync(It.IsAny<string>()))
            .ReturnsAsync(true);
    }
}