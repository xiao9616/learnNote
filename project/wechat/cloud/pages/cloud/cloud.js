// pages/cloud/cloud.js
wx.cloud.init()
const db=wx.cloud.database()
Page({

  /**
   * 页面的初始数据
   */
  data: {
    images:[]
  },

  insert:function(){
    db.collection('user').add({
      data:{
        age:20,
        name:'xuan'
      },
      success:res=>{
        console.log(res);
      }
    })
  },

  update:function(){
    db.collection('user').doc('57896b495ce2bd180272d6a11807fc09').update({
      data:{
        name:'wen'
      }
    }).then(res=>{
      console.log(res);
    }).catch(err=>{
      console.log(err);
    })
  },

  delete:function(){
    db.collection('user').doc('57896b495ce2bd180272d6a11807fc09').remove(

    ).then(res=>{
      console.log(res);
    }).catch(err=>{
      console.log(err);
    })
  },
  search:function(){
    db.collection('user').where({
      name:'xiao'
      }).get().then(res=>{
        console.log(res);
      }).catch(err=>{
        console.log(err)
      })
  },
  add:function(){
    wx.cloud.callFunction({
        name:'add',
        data:{
          a:2,
          b:3
        }
    }).then(res=>{
      console.log(res);
    }).catch(err=>{
      console.log(err);
    });
  },

  getopenid:function(){
    wx.cloud.callFunction({
      name:'login'
    }).then(res=>{
      console.log(res);
    }).catch(err=>{
      console.log(err);
    })
  },

  upload:function(){
    wx.chooseImage({
      count:1,
      sizeType:['original','compressed'],
      sourceType:['album','camera'],
      success: function(res) {
        const tempFilePath=res.tempFilePaths
        wx.cloud.uploadFile({
          cloudPath:new Date().getTime()+'.png',
          filePath:tempFilePath[0],
          success:res=>{
            console.log(res.fileID);
            db.collection('image').add({
              data:{
                fileID:res.fileID,
              }
            })
          },
          fail:console.error
        })
      }
    })
  },

  download:function(){
    wx.cloud.callFunction({
      name:'login',
    }).then(res=>{
      db.collection('image').where({
        _openid:res.result.openid
      }).get().then(res2=>{
        this.setData({
          images:res2.data
        })
      })
    })
  },

  save:function(event){
    wx.cloud.downloadFile({
      fileID:event.target.dataset.fileid,
      success:res=>{
        wx.saveImageToPhotosAlbum({
          filePath: res.tempFilePath,
          success(res){
            wx.showToast({
              title: '保存成功',
            })
          }
        })
      }
    })
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {

  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  }
})