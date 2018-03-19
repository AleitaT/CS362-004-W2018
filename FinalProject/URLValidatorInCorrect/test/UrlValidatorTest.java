import junit.framework.TestCase;
import java.util.concurrent.ThreadLocalRandom;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!



public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://10.0.0.225"));
	   System.out.println(urlVal.isValid("https://10.0.0.225"));
	   System.out.println(urlVal.isValid("ftp://10.0.0.225"));
	   System.out.println(urlVal.isValid("file://10.0.0.225"));
	   System.out.println(urlVal.isValid("http://10.0.0.225:32"));
	   System.out.println(urlVal.isValid("http://10.0.0.225:322"));
	   System.out.println(urlVal.isValid("http://10.0.0.225:3222"));
	   System.out.println(urlVal.isValid("http://10.0.0.225:3222"));
	   System.out.println(urlVal.isValid("https://google.com"));
	   System.out.println(urlVal.isValid("htp://www.google.com"));
	   System.out.println(urlVal.isValid("https://www.google.com"));
	   System.out.println(urlVal.isValid("ftp://www.google.com:102"));
	   System.out.println(urlVal.isValid("http://www.google.com?x=1"));
	   System.out.println(urlVal.isValid("http://www.google.com?x"));
	   System.out.println(urlVal.isValid("http://www.google.com?x\0"));
	   System.out.println(urlVal.isValid("http://www.google.com?x\n"));
	   System.out.println(urlVal.isValid("http://www.google.com:65535"));
	   System.out.println(urlVal.isValid("http://www.google.com:1024"));
	   System.out.println(urlVal.isValid("http://www.google.com?x=1"));
	   System.out.println(urlVal.isValid("http://www.google.com?x"));
	   System.out.println(urlVal.isValid("http://www.google.com?x\0"));
	   System.out.println(urlVal.isValid("http://www.google.com?x\n"));	   
	   System.out.println(urlVal.isValid("http://10.0.0.225:3000"));

   }
   
  /* INPUT PARTITIONING
   * The URLs were split by the five types to test for correctness:
   *  Scheme, Authority, Port, Path, and Query are all tested
   *  individually to allow for faster partition testing cases.
   */
   
   // Scheme Partition Testing
   public void testSchemetPartition()
   {
	   System.out.println("\n-----SCHEME PARTITION TEST-----");
	   String[] testSchemes = {"http://", "h3tp://", ":/", ":-", " "};
	   UrlValidator schemeVal = new UrlValidator(testSchemes, 0);
	   
	   for(int i = 0; i < testSchemes.length; i++)
	   {
		   String currScheme = testSchemes[i];
		   System.out.println("\nTesting Scheme: " + currScheme);
		   boolean valid = schemeVal.isValidScheme(currScheme);
		   
		                if(valid == false && i == 0 ||
				   valid == false && i == 1 ||
				   valid == true && i == 2 ||
				   valid == true && i == 3 ||
				   valid == false && i == 4)
		   {
			   if(i == 0) {System.out.println("TEST FAILED! Expected: Pass, Result: Fail");}
			   if(i == 1) {System.out.println("TEST FAILED! Expected: Pass, Result: Fail");}
			   if(i == 2) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 3) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 4) {System.out.println("TEST FAILED! Expected: Pass, Result: Fail");}
		   }
		   else
		   {
			   if(i == 0) {System.out.println("TEST PASSED! Expected: Pass, Result: Pass");}
			   if(i == 1) {System.out.println("TEST PASSED! Expected: Pass, Result: Pass");}
			   if(i == 2) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 3) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 4) {System.out.println("TEST PASSED! Expected: Pass, Result: Pass");}
		   }
	   }

   }
   
   // Authority Partition Testing
   public void testAuthorityPartition(){
	   System.out.println("\n-----AUTHORITY PARTITION TEST-----");
	   String[] testAuthorities = {"www.google.com", "www.google!.com", "www.google", " ", "not.working.com"};
	   UrlValidator authVal = new UrlValidator(testAuthorities, 0);
	   
	   for(int i = 0; i < testAuthorities.length; i++)
	   {
		   String currAuthority = testAuthorities[i];
		   System.out.println("\nTesting Authority: " + currAuthority);
		   boolean valid = authVal.isValidAuthority(currAuthority);
		    
		   // Based on expected values 
		                if(valid == false && i == 0 ||
				   valid == true && i == 1 ||
				   valid == true && i == 2 ||
				   valid == true && i == 3 ||
				   valid == true && i == 4)
		   {
			   if(i == 0) {System.out.println("TEST FAILED! Expected: Pass, Result: Fail");}
			   if(i == 1) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 2) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 3) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 4) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
		   }
		   else
		   {
			   if(i == 0) {System.out.println("TEST PASSED! Expected: Pass, Result: Pass");}
			   if(i == 1) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 2) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 3) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 4) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
		   }

	   }
   }
   
   // Port Partition Testing
   public void testPortPartition()
   {
	   System.out.println("\n-----PORT PARTITION TEST-----");
	   String[] testPorts = {"www.google.com:80", "www.google.com:-80", "www.goole.com:80a", ":", " " };
	   UrlValidator portVal = new UrlValidator(testPorts, 0);
	   
	   for(int i = 0; i < testPorts.length; i++)
	   {
		   String currPort = testPorts[i];
		   System.out.println("\nTesting Port: " + currPort);
		   boolean valid = portVal.isValidAuthority(currPort);
		   
		                if(valid == false && i == 0 ||
				   valid == true && i == 1 ||
				   valid == true && i == 2 ||
				   valid == true && i == 3 ||
				   valid == true && i == 4)
		   {
			   if(i == 0) {System.out.println("TEST FAILED! Expected: Pass, Result: Fail");}
			   if(i == 1) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 2) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 3) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 4) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
		   }
		   else
		   {
			   if(i == 0) {System.out.println("TEST PASSED! Expected: Pass, Result: Pass");}
			   if(i == 1) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 2) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 3) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 4) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
		   }

	   }
   }
   
   // Path Partition Testing
   public void testPathPartition()
   {
	   System.out.println("\n-----PATH PARTITION TEST-----");
	   String[] testPaths = {"/test", "/", "test", "//test", ".."};
	   UrlValidator pathVal = new UrlValidator(testPaths, 0);
	   
	   for(int i = 0; i < testPaths.length; i++)
	   {
		   String currPath = testPaths[i];
		   System.out.println("\nTesting Path: " + currPath);
		   boolean valid = pathVal.isValidPath(currPath);
		   
		                if(valid == false && i == 0 ||
				   valid == false && i == 1 ||
				   valid == true && i == 2 ||
				   valid == true && i == 3 ||
				   valid == true && i == 4)
		   {
			   if(i == 0) {System.out.println("TEST FAILED! Expected: Pass, Result: Fail");}
			   if(i == 1) {System.out.println("TEST FAILED! Expected: Pass, Result: Fail");}
			   if(i == 2) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 3) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 4) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
		   }
		   else
		   {
			   if(i == 0) {System.out.println("TEST PASSED! Expected: Pass, Result: Pass");}
			   if(i == 1) {System.out.println("TEST PASSED! Expected: Pass, Result: Pass");}
			   if(i == 2) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 3) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 4) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
		   }

	   }
   }
   
   // Query Partition Testing
   public void testQueryPartition()
   {
	   System.out.println("\n-----QUERY PARTITION TEST-----");
	   String[] testQueries = {"?action=view", "?/", "/", "??action=view", " "};
	   UrlValidator queryVal = new UrlValidator(testQueries, 0);
	   
	   for(int i = 0; i < testQueries.length; i++)
	   {
		   String currQuery = testQueries[i];
		   System.out.println("\nTesting Query: " + currQuery);
		   boolean valid = queryVal.isValidQuery(currQuery);
		   
		                if(valid == false && i == 0 ||
				   valid == true && i == 1 ||
				   valid == true && i == 2 ||
				   valid == true && i == 3 ||
				   valid == true && i == 4)
		   {
			   if(i == 0) {System.out.println("TEST FAILED! Expected: Pass, Result: Fail");}
			   if(i == 1) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 2) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 3) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
			   if(i == 4) {System.out.println("TEST FAILED! Expected: Fail, Result: Pass");}
		   }
		   else
		   {
			   if(i == 0) {System.out.println("TEST PASSED! Expected: Pass, Result: Pass");}
			   if(i == 1) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 2) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 3) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
			   if(i == 4) {System.out.println("TEST PASSED! Expected: Fail, Result: Fail");}
		   }

	   }
   }
   
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   
	   String[] validSchemes = {"http", "https"};
	   
	   boolean isValid = true; 
	   UrlValidator urlValidator = new UrlValidator(validSchemes, UrlValidator.NO_FRAGMENTS);
	   int randomNum;
	  
	   boolean testResult = true;
	   
	   String[] goodScheme = {"http://", "ftp://", "https://", "sftp://"};   
   
	   String[] badScheme = {"ptth://", "//ht:", ":////", "http"};
	   
	   String[] goodUrl = {"www.facebook.com", "www.amazon.com", "www.google.com", "main.oregonstate.edu"};
	   
	   String[] badUrl = {"999.999.999.999", "com.ww", "bbb.amazon.com", "...//www/com"};
	   
	   String[] goodPath = {"/path","/2345","/path356/","/123?query&=this"};
	   
	   String[] badPath = {"pathProblem","/.../","/324//32","/pathOk?//notOk"};

	   for(int i = 0; i < 100; i++) {

		   StringBuilder URLTest = new StringBuilder();
		   isValid = true;
		   for(int j = 0; j < 3; j++) {
			   randomNum = ThreadLocalRandom.current().nextInt(1, 3);
			   if(j == 0){
				   if(randomNum == 1) {
					   randomNum = ThreadLocalRandom.current().nextInt(0, 4);
					   URLTest.append(goodScheme[randomNum]);
					   
				   }else {
					   randomNum = ThreadLocalRandom.current().nextInt(0, 4);

					   URLTest.append(badScheme[randomNum]);
					   isValid = false;
				   }
			   }
			   
			   if(j == 1) {
				   if(randomNum == 1) {
					   randomNum = ThreadLocalRandom.current().nextInt(0, 4);

					   URLTest.append(goodUrl[randomNum]);
					   
				   }else {
					   randomNum = ThreadLocalRandom.current().nextInt(0, 4);

					   URLTest.append(badUrl[randomNum]);
					   isValid = false;
				   }
			   }			 
			   
			   if(j == 2) {
				   if(randomNum == 1) {
					   randomNum = ThreadLocalRandom.current().nextInt(0, 4);

					   URLTest.append(goodPath[randomNum]);
					   
				   }else {
					   randomNum = ThreadLocalRandom.current().nextInt(0, 4);

					   URLTest.append(badPath[randomNum]);
					   isValid = false;
				   }				   
			   }
		   } 
		   
		   String urlString = URLTest.toString();
		   testResult = urlValidator.isValid(urlString);
		   System.out.printf("Test Case: %d\n", i);
		   if(testResult == true) {
			   if(isValid == false) {
				   System.out.println("TEST FAILED! Expected: Fail, Result: Pass");
				   System.out.printf("URL: %s\n\n", urlString);
				   
			   }
			 
		   } else {
			   if(isValid == true) {
				   
				   System.out.println("TEST FAILED! Expected: Pass, Result: Fail");
				   System.out.printf("URL: %s\n\n", urlString);
			   }
		   }
		   
		   if(testResult && isValid) {
			   System.out.println("TEST PASSED! Good URL");
			   System.out.printf("URL: %s\n\n", urlString);
		   }
		   
		   if(!testResult && !isValid) {
			   
			   System.out.println("TEST PASSED! Bad URL");
			   System.out.printf("URL: %s\n\n", urlString);
		   }
		   
	   } 			
   }   
}
