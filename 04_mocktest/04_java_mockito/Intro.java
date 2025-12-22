// State testing - verifies the outcome/result
@Test
void testEmailNotificationSent() {
    NotificationService service = new NotificationService(emailClient);

    service.sendWelcomeEmail("user@example.com");

    // Verify the final state or return value
    assertTrue(service.getLastEmailStatus().isSuccess());
}

// Behavior testing - verifies method interactions
@Test
void testEmailClientCalledCorrectly() {
    NotificationService service = new NotificationService(emailClientMock);

    service.sendWelcomeEmail("user@example.com");

    // Verify specific method calls occurred
    verify(emailClientMock).sendEmail(
        eq("user@example.com"),
        eq("Welcome!"),
        contains("Welcome to our platform")
    );
}
