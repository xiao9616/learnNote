// pages/photo/photo.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    src:null,
    result:null,
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    wx.getSetting({
      success(res){
        if(!res.authSetting['scope.writePhotosAlbum']){
          wx.authorize({
            scope: 'scope.writePhotosAlbum',
            success(res){
              console.log("success")
            }
          })
        }
      }
    })
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
    
  },

  takePhoto:function(){
    const ctx = wx.createCameraContext()
    ctx.takePhoto({
      quality: 'high',
      success: (res) => {
        this.setData({
          src: res.tempImagePath
        })
        wx.uploadFile({
          url: 'http://172.28.4.109:5000/upload',
          filePath: res.tempImagePath,
          name: 'image',
          header: { "Content-Type": "multipart/form-data" },
        })
      }
    })
    
    wx.downloadFile({
      url: 'http://172.28.4.109:5000/image',
      success: res => {
        result: res.data
      }
    })
    
  },

  savePhoto:function(){
    
    wx.saveImageToPhotosAlbum({
      filePath:this.data.result,
      success(res) { 
        wx.showToast({
          title: '成功保存到相册',
          icon:'success',
          mask:true,
          duration:1000
        })
      }
    })
  }
})
