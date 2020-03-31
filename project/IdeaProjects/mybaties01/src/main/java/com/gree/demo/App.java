package com.gree.demo;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.Reader;

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
