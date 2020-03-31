# Spring

## 介绍

### 依赖注入/DI

框架创建了类所依赖的对象，然后把这些对象传给（注入）依赖它们的类，这就是“依赖注入”。

### 控制反转/IOC

本来由类控制其所依赖的类对象的创建，现在把创建动作放到Spring框架里了，由框架控制所有类对象的创建，这就是“控制反转”。

### 面向切面编程/AOP

面向切面编程的主要作用是，在不修改源代码的情况下，可以给目标类打补丁，让其执行补丁中的代码。

例如，用户类中有个登录方法，现在需要加用户登录日志。使用AOP就不需要修改用户登录方法，只需把日志代码注入到用户登录方法前后，让其执行。日志代码就是“切面”，插入代码的地方（用户类的登录方法）就是“连接点”。

## 模块

### 核心容器

- **Spring Core**：这个模块是Spring框架的核心，提供控制反转/依赖注入功能
- **Spring Bean**：这个模块实现Bean的工厂模式，Bean可以理解为组件，是JEE中基本的代码组织单位，Spring中Bean形式是普通Java类
- **Spring Context**：此模块表示Spring应用的环境，通过此模块可访问任意Bean，`ApplicationContext`接口是模块的关键组成
- **Spring表达式语言(SpEL)**：这个模块提供对表达式语言(SpEL)支持

### Spring数据访问/集成

- **JDBC**：对Java JDBC接口再次包装，让Spring应用中使用JDBC更简单
- **ORM**: ORM代表对象关系映射，该模块提供对ORM的支持
- **OXM**: OXM代表对象XML映射器，该模块提供对OXM的支持
- **JMS**: JMS代表Java消息传递服务，该模块提供对JMS的支持
- **事务**: 该模块提供数据库事务的支持

### Spring Web

- **web**：提供基本的Web功能，如文件下载、rest接口支持等
- **web-servlet**：实现MVC（Model-View-Controller）功能
- **web socket**：提供对web socket的支持
- **web portlet**：提供对web portlet的支持

### 其他模块

- **AOP** 提供对面向切面编程的支持
- **Aspects** 提供与AspectJ集成，AspectJ是另一个面向切面编程的框架
- **Instrumentation** 提供在某些应用服务器中使用的类加载实现
- **Messaging** 提供对STOMP(Simple (or Streaming) Text Oriented Message Protocol )的支持
- **Test** 支持JUnit或TestNG框架测试Spring组件

## Maven配置POM

### spring-context

```
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-context</artifactId>
    <version>4.3.13.RELEASE</version>
</dependency>
```

### Junit4

```
<dependency>
    <groupId>junit</groupId>
    <artifactId>junit</artifactId>
    <version>4.12</version>
    <scope>test</scope>
</dependency>
```

### spring-test

```
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-test</artifactId>
    <version>4.3.13.RELEASE</version>
</dependency>
```

## 注解

注解写在实现类上,不写在接口上interface

### @Component

spring为其自动创建对象

### @Primary

使得该类所产生的对象具有高优先级

### @Qualifier

限定符号,指定Bean的名称

### @Autowired

自动创建对象之间的关联关系,自动注入Component的对象

require参数用来确定是否检查对象是否创建,默认为true

```
 @Autowired(required = false)
 public void setService(MessageService service) {
     this.service = service;
 }
```

**Autowired使用的场景**

1.注入构造函数

```
 @Autowired
 public void setService(MessageService service) {
     this.service = service;
 }
```

2.注入成员变量

```
 @Autowired
 private MessageService seivice;
```

3.set方法

```
 @Autowired
 public setService(MessageService seivice){
 	this.service=service;
 }
```

4.任意的函数

**例子:**

首先配置spring-context

MessagePrinter:

```
package hello;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class MessagePrinter {
    public MessagePrinter() {
        System.out.println("message printer");
    }

    private MessageService service;

    @Autowired
    public void setService(MessageService service) {
        this.service = service;
    }

    public void printMessage() {
        String s = service.getMessage();
        System.out.println(s);
    }
}
```

MessageService:

```
package hello;

import org.springframework.stereotype.Component;

//打印
@Component
public class MessageService {
    public MessageService() {
        System.out.println("message service");
    }

    public String getMessage() {
        return "hello world!";
    }
}
```

使用@Component为类创建对象,利用@Autowired进行依赖注入,@ComponentScan进行扫描

```
package hello;

import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.ComponentScan;

@ComponentScan
public class ApplicationSpring {
    public static void main(String[] args) {
        System.out.println("applicationSpring");
        //初始化spring容器
        ApplicationContext contex = new AnnotationConfigApplicationContext(ApplicationSpring.class);
        //从容器中获取对象
        MessagePrinter printer = contex.getBean(MessagePrinter.class);

        printer.printMessage();
    }
}
```

```
ApplicationContext contex = new AnnotationConfigApplicationContext(ApplicationSpring.class);
```

AnnotationConfigApplicationContext生成一个spring容器,从容器中获取Bean(对象)

为了使得@ComponentScan和mian解耦,单独创建一个配置类Appconfig.

### @ComponentScan

扫描Component,默认扫描本包,如果需要扫描外部包需要@ComponentScan("com.package.demo")

或者扫描多个包@ComponentScan(basePackage={"com.package.demo","com.package.web"})  //类型不安全

@ComponentScan(basePackageClasses={UserService.class,UserController.class})

### @Configuration

@Configuration表示是一个配置类

```
@Configuration
@ComponentScan
public class AppConfig {

}
```

```
ApplicationContext contex = new AnnotationConfigApplicationContext(Appconfig.class);
```

### @RunWith(SpringJUnit4ClassRunner.class)

装配Junit4

### @ContextConfiguration(classes = AppConfig.class)

**配置XML文件就是@ContextConfiguration("classpath:applicationconfig.xml")**

配置上下文,加载配置类

```
package hello;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes = AppConfig.class)
public class AppTest {
    @Autowired
    private MessagePrinter printer;
    @Test
    public void testprint() {
        printer.printMessage();
    }
}
```

### @Bean

### @Scope

参数为singleton,prototype,session,requeset

用来确定Bean对象每次是重新生成还是单例模式

### @Lazy

scope设置为singleton时,bean的创建为按需启动(懒汉式,默认为饿汉式)

### @PostConstruct/@PreDestray

定义bean初始化方法和销毁方法

## Spring AOP



## 常见问题

### 装配Bean的三种方式

#### 方式1:隐藏bean发现和自动装配(注解的方式)

@Component @Autowired

```
ApplicationContext contex = new AnnotationConfigApplicationContext(ApplicationSpring.class);
```

#### 方式2:XML中显示方式

resources下面新建文件applicationContext.xml

```
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
    <bean id="service" class="hello.MessageService"></bean>
    <bean id="printer" class="hello.MessagePrinter">
        <property name="service" ref="service"></property>
    </bean>
</beans>
```

<bean>用来加载类为对象,<property>用来依赖注入

```
ApplicationContext contex = new ClassPathXmlApplicationContext("applicationContext.xml");
```

**Bean的作用域与启动**

```
<bean id="notepad" class="com.gree.demo.Notepad" scope="prototype" lazy-init="true" />
```

single:单例,在整个应用程序中,只创建一个实例

prototype:每次注入或者从spring上下文获取,都会创建一个新的实例

session:在web应用中,为每个会话创建一个bean实例

request:在web应用中,为每个请求创建一个bean实例



加载方式默认为饿汉式,通过设置lazy-init="true"为懒汉式启动

**获取Bean的方式有两种**

```
MessagePrinter printer = context.getBean(MessagePrinter.class);
```

```
MessagePrinter printer = (MessagePrinter) context.getBean("printer");
```

**工厂方法创建bean对象**

静态工厂

```
<bean id="notepad" class="com.gree.demo.Notepad" factory-method="createNotepad"/>
```

实例工厂

```
<bean id="factory" class="com.gree.demo.Notepad" />
<bean id="notepad" factory-bean="factory" factory-method="createNotepad"/>
```

**<bean>对象中id和name的区别**

```
<bean name="service service1" class="hello.MessageService"></bean>
```

service1是service的别名

**使用XML进行依赖注入**

注入构造函数

```
<constructor-arg ref="service"></constructor-arg>
```

使用C命名空间注入构造函数

```
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:c="http://www.springframework.org/schema/c"
	<bean id="printer" class="hello.MessagePrinter" c:service-ref="service">
</beans>
```

简单类型注入

```
<bean id="service" class="hello.MessageService">
	<constructor-arg name="name" value="s1"></constructor-arg>
</bean>
```

List注入

```
<bean id="service" class="hello.MessageService">
    <constructor-arg name="list">
        <list>
        	<value>"123"</value>
        </list>
    </constructor-arg>
</bean>
```

属性注入和set方法有关

```
<bean id="printer" class="hello.MessagePrinter">
	<property name="service" ref="service"></property>
</bean>
```

#### 方式3:Java中显示配置

当无法修改包内的代码又需要进行组件扫描的话,就需要显示的配置,而不能自动配置了.

同样的方式创建AppConfig类

```
@Configuration
public class AppConfig {
    @Bean
    @Scope(ConfigurableBeanFactory.SCOPE_PROTOTYPE)
    public UserDao userDaoNormal() {
        return new UserDaoNormal();
    }
    
    //注入
    @Bean
    public UserServiceNormal userServiceNormal(UserDao userDao) {
        return new UserServiceNormal(userDao);
    }
}
```

### 解决自动装配时Bean冲突

定义接口UserService

```
public interface UserService {
    public void add();
}
```

实现类userServiceNormal,UserServiceFestival

```
@Component
public class UserServiceNormal implements UserService {
    public void add() {
        System.out.println("添加用户");
    }
}
```

```
@Component
public class UserServiceFestival implements UserService {
    @Override
    public void add() {
        System.out.println("添加用户节日");
    }
}
```

在测试过程中autowired对象时就不知道用哪个对象来进行注入了,这就是bean冲突

```
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes = Appconfig.class)
public class UserServiceTest {
    @Autowired
    private UserService userService;

    @Test
    public void testAdd() {
        userService.add();
    }
}
```

#### 方式一:首选Bean

在需要优先的地方添加@Primary注解

```
@Component
@Primary
public class UserServiceFestival implements UserService {
    @Override
    public void add() {
        System.out.println("添加用户节日");
    }
}
```

#### 方式二:限定符

为UserServiceFestival和Normal分别添加限定符@Qualifier("festival")和@Qualifier("normal")

```
@Component
@Primary
@Qualifier("festival")
public class UserServiceFestival implements UserService {
    @Override
    public void add() {
        System.out.println("添加用户节日");
    }
}
```

在测试中指定注入哪个bean

```
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes = Appconfig.class)
public class UserServiceTest {
    @Autowired
    @Qualifier("normal")
    private UserService userService;

    @Test
    public void testAdd() {
        userService.add();
    }
}
```

#### 方式三:使用类id

使用@Component添加类id,如果Component没有参数,spring会给一个默认类id(类名字全小写).比如UserServiceFestival的id就是userservicefestival

```
@Component("festival")
public class UserServiceFestival implements UserService {
    @Override
    public void add() {
        System.out.println("添加用户节日");
    }
}
```

还是需要通过Qualifier来指定使用哪个Bean

```
@Autowired
@Qualifier("festival")
private UserService userService;
```

# ServLet

## 概念

Java web服务器：处理客户端发送的HTTP请求，然后把http响应返回给客户端的应用软件

web容器：也称为Servlet容器或Servlet引擎，是Web服务器中处理servlet交互、管理servlet生命周期的软件模块，有时不严格区分服务器与容器，如tomcat可以说是容器也可说是web服务器

web应用(webapp)：一个web应用程序，如新闻网站，一个web应用可以包含多个servlet



Java Servlet是处理HTTP请求的Java对象.Javaweb服务器可以同时运行多个Java Web应用程序，Java Web应用程序可以包含多个Servlet。Java web应用程序也可以包含servlet之外的其他组件，如Java Server Pages (JSP)。

访问过程:浏览器向Java web服务器发送一个HTTP请求，web服务器检查请求是否指向某个servlet，如果是，servlet容器将找出目标servlet，然后将请求传递给目标servlet处理。容器通过调用servlet.service()方法处理请求，并生成响应返回给浏览器。

## 生命周期

servlet遵循一定的生命周期，由servlet容器管理。生命周期包含以下过程:

加载Servlet类
创建Servlet实例
调用servlet init()方法
调用servlet service()方法
调用servlet destroy()方法

步骤1、2、3只在servlet初始加载时执行一次。默认情况下，servlet在没有收到请求时不会加载。但也可以在容器启动时强制加载servlet，后续内容会有说明。

步骤4会被多次执行 —— servlet每处理一个HTTP请求，都会执行一次`service()`。
步骤5在servlet容器卸载servlet时执行。

## 创建servlet

创建Servlet必须直接或间接地实现Servlet接口。

### 3种创建servlet的方法:

通过继承HttpServlet类
通过继承GenericServlet类
直接实现Servlet接口

### Servlet接口中的方法：

**void init(ServletConfig config):**当Servlet容器启动时(web服务器启动时触发)，容器会加载所有Servlet类并创建这些类的实例，然后调用每个servlet实例的init()方法进行初始化。

**void destroy():** 该方法在Servlet生命周期结束时由Servlet容器调用，用于释放资源。与多次调用的service()方法不同，Servlet容器在整个生命周期中只调用该方法一次。一旦destroy()方法被调用，servlet容器就不会调用该servlet的service()方法。

**void service(ServletRequest req, ServletResponse res):**这是servlet生命周期中唯一被多次调用的方法。这个方法处理客户端请求，每次服务器接收到请求时都会调用这个方法处理。

**ServletConfig getServletConfig():**返回一个ServletConfig对象，这个对象包含了servlet的初始化、启动参数信息。

**lang.String getServletInfo():**返回关于servlet的信息，如作者、版本、版权等信息。

```
public class MyServlet implements GenericServlet {

}
```

### GenericServlet:

GenericServlet是一个与具体协议无关的通用servlet，继承GenericServlet的子类通过重写service()方法来处理客户端请求。

```
public class MyServlet extends GenericServlet {

  public void service(ServletRequest request, ServletResponse response)
        throws ServletException, IOException {

       // 处理请求
  }
}
```

### HttpServlet:

javax.servlet.http.HttpServlet类是GenericServlet的子类，功能比GenericServlet强大。

HttpServlet类读取HTTP请求，检查该请求的类型（HTTP GET、POST、PUT、DELETE、HEAD等），然后调用请求类型对应的方法。

```
public class MyHttpServlet extends HttpServlet {

  protected void doGet( HttpServletRequest request,
                        HttpServletResponse response)
        throws ServletException, IOException {

      response.getWriter().write("<html><body>GET响应</body></html>");
  }
}
```

可以重写以下方法:

doGet()
doPost ()
doHead()
doPut ()
doDelete()
doOptions ()
doTrace ()

建议使用`HttpServlet`而不是`GenericServlet`，`HttpServlet`比`GenericServlet`更方便。

### HttpServletRequest

```
HttpServletRequest request;
String contentLength = request.getHeader("Content-Length");
InputStream requestBodyInput = request.getInputStream(); 
HttpSession session = request.getSession();
ServletContext context = request.getSession().getServletContext();
```

### HttpServletResponse

```
response.setHeader("Content-Type", "text/plain");
PrintWriter writer = response.getWriter();
writer.write("奇客谷纯文本")

//可以将二进制数据返回给浏览器，如图片、pdf文件等等。要设置Content-Type报头为合适的类型，如PNG图像的Content-Type是image/PNG。
//输出二进制数据不能使用response.getWriter()，这个只能用于文本，要使用response.getOutputStream()方法
OutputStream outputStream = response.getOutputStream();
outputStream.write(...);

//重定向
response.sendRedirect("http://qikegu.com");
```

### HttpSession

用户会话中包含了当前用户的相关信息，这些信息可以被同一个会话中多个HTTP请求访问。当用户第一次进入某个站点时，将为该用户提供唯一ID来标识这次会话。这个ID通常存储在cookie或URL参数中。会话对象中的值保存在servlet容器的内存中。

```
HttpSession session = request.getSession();

session.setAttribute("userName", "老吴");
String userName = (String) session.getAttribute("userName");
```

## 目录结构

为了让Java web服务器（Tomcat, Jetty）运行Java web应用程序，需按照标准目录结构打包Java web应用程序的资源(servlet、JSP等)。

```
webapp
	WEB-INF
		.xml	//配置文件
		classes	//编译后的class文件
		lib		//存放lib的jar包
	index.jsp
```

根目录下，除了WEB-INF目录，其他所有目录和文件都是开放访问的

如果你的web应用程序被映射到网址http://gree.com/webapp

```
http://gree.com/webapp/index.jsp
```

### WEB-INF目录

**web.xml:**

web.xml是部署配置文件，告诉web容器如何部署web应用程序。web容器在部署servlet时必须做好网址映射，我们才能通过网址访问该servlet.

```
<web-app>
  <display-name>Archetype Created Web Application</display-name>
  
  <servlet>
    <servlet-name>dispatcherServlet</servlet-name>
    <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
  </servlet>
  
  <servlet-mapping>
    <servlet-name>dispatcherServlet</servlet-name>
    <url-pattern>*.html</url-pattern>
  </servlet-mapping>
  
</web-app>
```

<servlet>元素中配置servlet的名称，类名.

<servlet-mapping>元素中配置servlet的网址映射，这里的配置表明所有以.html结尾的URL都将被映射.

```
<servlet>
    <servlet-name>myServlet</servlet-name>
    <servlet-class>com.qikegu.demo.MyServlet</servlet-class>

        <init-param>
            <param-name>myParam</param-name>
            <param-value>paramValue</param-value>
        </init-param>
</servlet>
```

给servlet设置初始化参数，参数只限该servlet访问

```
public class MyServlet extends GenericServlet {

	protected String myParam = null;
	
	public void init(ServletConfig servletConfig) throws ServletException{
    	this.myParam = servletConfig.getInitParameter("myParam");
  }
}
```

如果没有设置<load-on-startup>，web容器通常会在首个请求到达时加载servlet，反之如果设置了<load-on-startup>，web容器启动时会立即加载servlet.

```
<servlet>
    <servlet-name>myServlet</servlet-name>
    <servlet-class>com.qikegu.demo.MyServlet</servlet-class>

    <load-on-startup>1</load-on-startup>
</servlet>
```

context参数的作用范围是整个web应用，web应用内的所有servlet都可以访问

```
<web-app>
    <context-param> 
        <description>管理员邮件地址</description> 
        <param-name>webmaster</param-name> 
        <param-value>admin@qikegu.com</param-value> 
    </context-param> 
</web-app>
```

```
String myContextParam =request.getSession().getServletContext().getInitParameter("webmaster");
```

**classes:**

classes目录包含web应用程序中的全部已编译Java类。

**lib:**

lib目录包含web应用程序用到的全部JAR包文件。此目录通常包含的是第三方库文件，但你也可以将自己的类文件打成JAR包放在这里，而不是将这些类放入classes目录中。

## Cookie

cookie是web服务端程序存储在浏览器上的数据,长度最多4千字节.

```
Cookie cookie = new Cookie("myCookieName", "myCookieValue");
response.addCookie(cookie);
```

当访问某个网站时，浏览器会自动上传由该网站保存在浏览器里的Cookie。浏览器只上传该网站的Cookie，不会上传其他网站的。

可以通过HttpServletRequest读取Cookie:

```
Cookie[] cookies = request.getCookies();
```

设置Cookie过期时间,Cookie过期之后会被浏览器自动删除

```
Cookie cookie = new Cookie("uid", "123456");
cookie.setMaxAge(72 * 60 * 60);  // 72 小时
response.addCookie(cookie);
```

主动删除Cookie,通过设置过期时间为0或-1删除Cookie，0立即删除，-1浏览器关闭时删除。

```
cookie.setMaxAge(0);
```

Cookie使用场景:
存储session ID，与session机制结合，实现用户登录机制；
存储用户相关信息，如访问电商网站时，可以存储浏览过的商品信息，之后可以根据这些信息向用户推荐商品，搜索引擎可以利用Cookie保存搜索记录.

## Filter

servlet过滤器(Filter)可以拦截servlet、JSP、HTML以及其他静态内容的http请求.继承javax.servlet.Filter接口

```
public class MyServletFilter implements Filter {
	    public void init(FilterConfig filterConfig) throws ServletException {
    }

    public void doFilter(ServletRequest request, ServletResponse response,
                         FilterChain filterChain)
    throws IOException, ServletException {

    }

    public void destroy() {
    }
}
```

执行过滤的是doFilter()方法

```
public void doFilter(ServletRequest request, ServletResponse response, 
    FilterChain filterChain) throws IOException, ServletException {

    String myParam = request.getParameter("myParam");

    if(!"block".equals(myParam)){
        filterChain.doFilter(request, response);
    }
}
```

配置web.xml

```
<filter>
    <filter-name>myFilter</filter-name>
    <filter-class>servlets.MyServletFilter</filter-class>
</filter>

<filter-mapping>
    <filter-name>myFilter</filter-name>
    <url-pattern>*.test-filter</url-pattern>
</filter-mapping>
```

URL以.test-filter结尾的所有请求都将被servlet过滤器拦截，其他的不会受到影响。

# MyBatis

## 介绍

MyBatis 通过将参数映射到配置的 SQL 形成最终执行的 SQL 语句，最后将执行 SQL 的结果映射成 Java 对象返回。

MyBatis 核心特性：

1.通过动态SQL与参数绑定，避免复杂的SQL语句拼接
2.结果集自动映射成 Java 对象返回

 MyBatis 并没有将 Java 对象与数据库表关联起来，而是将 Java 方法与 SQL 语句关联

当一条 SQL 语句被标记为“可缓 存”后，首次执行它时从数据库获取的所有数据会被存储在高速缓存中，后面再执行这条语句 时就会从高速缓存中读取结果，而不是再次命中数据库。

## 配置

### 配置Maven

```
<dependencies>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.17</version>
    </dependency>

    <dependency>
        <groupId>org.mybatis</groupId>
        <artifactId>mybatis</artifactId>
        <version>3.5.2</version>
    </dependency>
</dependencies>
```

### 配置MyBatis

连接数据库的配置,以及对应的映射文件

MybatisConfig.xml

```
<environments default="development">
    <environment id="development">
    <transactionManager type="JDBC"/>
        <dataSource type="UNPOOLED">
            <property name="driver" value="com.mysql.jdbc.Driver"/>
            <property name="url" value="jdbc:mysql://localhost:3306/qikegu_mybatis"/>
            <property name="username" value="root"/>
            <property name="password" value="root"/>
        </dataSource>
	</environment>
</environments>

<mappers>
	<mapper resource="UserMapper.xml"/>	
</mappers>


//类型别名标签,配置好后，可在MyBatis映射文件中直接使用User
<typeAliases>
	<typeAlias type="com.gree.demo.User" alias="User"/>
</typeAliases>
```

### 配置映射文件

UserMapper.xml

考虑到有类User

```
public class User {
    private long id;
    private String name;

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public User(long id, String name) {
        this.id = id;
        this.name = name;
    }

    public User() {
    }
}
```

为其配置映射文件

UserMapper.xml

```
<mapper namespace="com.gree.demo">

    <insert id="insert" parameterType="User">
        INSERT INTO User (name) VALUES (#{name});

        <selectKey keyProperty="id" resultType="long" order="AFTER">
            select
            last_insert_id() as id
        </selectKey>

    </insert>

    <resultMap id="result" type="User">
        <result property="id" column="id"/>
        <result property="name" column="name"/>
    </resultMap>

    <select id="getAll" resultMap="result">
        SELECT * FROM User;
    </select>

    <select id="getById" parameterType="long" resultMap="result">
        SELECT *
        FROM User WHERE ID = #{id};
    </select>

    <update id="update" parameterType="User">
        UPDATE User SET name = #{name}
        WHERE ID = #{id};
    </update>

    <delete id="deleteById" parameterType="long">
        DELETE from User WHERE id = #{id};
    </delete>

</mapper>
```

main可以这样调用

```
public class App {
    public static void main(String[] args) throws IOException {
        Reader reader = Resources.getResourceAsReader("MyBatisConfig.xml");
        SqlSessionFactory build = new SqlSessionFactoryBuilder().build(reader);
        SqlSession sqlSession = build.openSession();

        User xiao = new User(10, "xiao");
        sqlSession.insert("insert", xiao);
        sqlSession.commit();
        sqlSession.close();
    }
}
```

# SpringMVC

## 介绍

**MVC:**

model模型(java bean) view视图(jsp) controller控制器(severlet)

**服务器端的三层框架:**

**表现层SpringMVC:**接收web请求和响应结果

**业务层Spring:**处理业务逻辑

**持久层Mybaties:**存储数据

**SpringMVC:**

# SpringBoot

## 介绍

Spring Boot是一个基于spring框架的项目模板，用于简化Spring应用开发。开发spring应用时，总有很多繁琐的配置要做，spring boot把这部分工作替我们做了。有如下特点:

简化繁琐的spring配置（xml/java 配置）；
提供内嵌的http服务器（tomcat/jetty），每个spring boot应用都是独立的web服务，简化部署（这点特别适用于微服务）；
简化maven依赖配置；
提供运行监测工具；

## 配置springboot(web)

```
<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>

    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-test</artifactId>
    <scope>test</scope>
    </dependency>
</dependencies>
```

### web demo

创建一个控制类,用来接到请求时对应的处理流程

```
@RestController
public class HelloController {
    @RequestMapping(value = "/hello",method = RequestMethod.GET)
    public String hello(){
        return "hello world";
    }
}
```

```
@SpringBootApplication
public class Springboot01Application {

    public static void main(String[] args) {
        SpringApplication.run(Springboot01Application.class, args);
    }

}
```

访问http://localhost:8080/hello就会接收到返回

## 注解

### @RestController

这个控制类提供Restful接口

### @RequestMapping

注解映射url请求

### @SpringBootApplication

应用类

@SpringBootApplication = (默认属性)@Configuration + @EnableAutoConfiguration + @ComponentScan。

### @MapperScan("com.gree.springboot02.repository")

扫描mybatis映射类的路径，放在应用类的前面扫描

## 数据库操作

**JDBC:**

Java应用通过JDBC接口访问数据库，JDBC（Java DataBase Connectivity/Java数据库连接）为各种数据库，如mysql、oracle等，提供一个统一的接口，应用程序通过JDBC执行各种SQL操作，如select、insert等等。

**JPA:**

JPA（Java Persistence API/Java持久层接口），是ORM（Object Relational Mapping/对象关系映射）的一个标准，ORM的作用是在数据库表与Java对象之间建立映射，理论上来说有ORM就无需直接通过SQL操作数据库了，通过Java对象即可，这样会方便很多，Hibernate是实现JPA标准的一个有名例子。JPA建立在JDBC之上，也是通过JDBC访问数据库。

**Mybatis:**

ORM有一些缺点，如过于笨重，比如在多表联合查询时相当繁琐，但直接使用原始的JDBC操作数据库过于低效，mybatis是现在互联网项目使用比较多的一个Java持久层库。虽然mybatis经常被和Hibernate比较，但mybatis不是JPA的一个实现，mybatis可以理解为加强版的SQL，实现了诸如动态SQL、结果集映射等，高效又不失灵活，个人倾向使用mybatis。同样的，mybatis建立在JDBC之上，通过JDBC访问数据库。

### 连接mysql

#### 配置

pom.xml

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
        
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-jdbc</artifactId>
        </dependency>
        
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <scope>runtime</scope>
        </dependency>
        
        <dependency>
            <groupId>org.mybatis.spring.boot</groupId>
            <artifactId>mybatis-spring-boot-starter</artifactId>
            <version>2.1.0</version>
        </dependency>
    
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-test</artifactId>
            <scope>test</scope>
        </dependency>
    </dependencies>
application.properties，该文件在 src -> main -> resources 目录，配置数据库连接：

```
server.port=8080
spring.datasource.driver-class-name=com.mysql.cj.jdbc.Driver
spring.datasource.url=jdbc:mysql://localhost:3306/qikegu_demo?serverTimezone=UTC&useUnicode=true&characterEncoding=utf8
spring.datasource.username=root
spring.datasource.password=root
```

#### 访问mysql

```
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HelloController {
    @Autowired
    JdbcTemplate jdbcTemplate;
    @RequestMapping(value = "/search", method = RequestMethod.GET)
    public String search(){
        String sql = "SELECT mobile FROM user WHERE id = ?";
        String mobile = (String) jdbcTemplate.queryForObject(sql, new Object[]{1}, String.class);
        return "hello" + mobile;
    }
}
```

### 集成Mybatis

一般boot项目的目录结构

```
java
	--package
		--common		//公用代码
		--config		//spring java配置文件
		--controller	//控制层
		--model			//对象层
		--repository	//数据库访问层
		--service		//服务层
	Application.java	//启动文件
resources
	--mapper			//mybatis sql映射xml文件
	application.properties	//应用配置文件
```

application.properties

```
server.port=8080
spring.datasource.driver-class-name=com.mysql.cj.jdbc.Driver
spring.datasource.url=jdbc:mysql://localhost:3306/qikegu_demo?serverTimezone=UTC&useUnicode=true&characterEncoding=utf8
spring.datasource.username=root
spring.datasource.password=root

#mybatis配置
#mybatis.type-aliases-package=com.gree.springboot02.model
mybatis.mapper-locations=classpath:mapper/*.xml
```

Application.java

```
package com.gree.springboot02;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@MapperScan("com.gree.springboot02.repository")
public class Springboot02Application {
    public static void main(String[] args) {
        SpringApplication.run(Springboot02Application.class, args);
    }

}
```

model/User.java

```
package com.gree.springboot02.model;
import com.fasterxml.jackson.annotation.JsonProperty;

public class User {
    private long id;
    private String nickname;
    private String mobile;

    @JsonProperty(access = JsonProperty.Access.WRITE_ONLY) //在输出的Json数据中隐藏密码，只能输入不输出
    private String password;

    private String role;

    public User(long id, String nickname, String mobile, String password, String role) {
        this.id = id;
        this.nickname = nickname;
        this.mobile = mobile;
        this.password = password;
        this.role = role;
    }

    public User() {
        super();
    }

    public String getNickname() {
        return nickname;
    }
    public void setNickname(String nickname) {
        this.nickname = nickname;
    }
    public long getId() {
        return id;
    }
    public void setId(long id) {
        this.id = id;
    }
    public String getMobile() {
        return mobile;
    }
    public void setMobile(String mobile) {
        this.mobile = mobile;
    }
    public String getPassword() {
        return password;
    }
    public void setPassword(String password) {
        this.password = password;
    }
    public String getRole() {
        return role;
    }
    public void setRole(String role) {
        this.role = role;
    }
}
```

service/UserService.java接口

```-
package com.gree.springboot02.service;

import com.gree.springboot02.model.User;

public interface UserService {
    public User getUserById(long userId);
}
```

service/UserServiceimpl.java实现

```
@Service("userService")
public class UserServiceImpl implements UserService {
    @Autowired
    private UserMapper userMapper;
    @Override
    public User getUserById(long userId) {
        return userMapper.selectByPrimaryKey(userId);
    }
}
```

repository/UserMapper.java

```
@Repository
public interface UserMapper {
    // 对应xml映射文件元素的ID
    User selectByPrimaryKey(long id);
}
```

controller/UserController.java

```
@RestController
@EnableAutoConfiguration
@RequestMapping("/user")
public class UserController {
    @Resource
    private UserService userService;
    @RequestMapping(value = "{id}", method = RequestMethod.GET, produces = "application/json")
    public User getUser(@PathVariable long id) throws Exception {
        User user = this.userService.getUserById(id);
        return user;
    }
}
```

resources/mapper/UserMapper.xml

```
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.gree.springboot02.repository.UserMapper">
    <resultMap id="BaseResultMap" type="com.gree.springboot02.model.User">
        <constructor>
            <idArg column="id" javaType="_long" jdbcType="BIGINT" />
            <arg column="nickname" javaType="java.lang.String" jdbcType="VARCHAR" />
            <arg column="mobile" javaType="java.lang.String" jdbcType="VARCHAR" />
            <arg column="password" javaType="java.lang.String" jdbcType="CHAR" />
            <arg column="role" javaType="java.lang.String" jdbcType="VARCHAR" />
        </constructor>
    </resultMap>

    <sql id="Base_Column_List">
    id, nickname, mobile, password, role
  </sql>
    <select id="selectByPrimaryKey" parameterType="_long" resultMap="BaseResultMap">
        select
        <include refid="Base_Column_List" />
        from user
        where id = #{id,jdbcType=BIGINT}
    </select>
</mapper>
```

