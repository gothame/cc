/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.freeswitch.esl;

public class ESLconnection {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected ESLconnection(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ESLconnection obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      eslJNI.delete_ESLconnection(swigCPtr);
    }
    swigCPtr = 0;
  }

  public ESLconnection(String host, int port, String user, String password) {
    this(eslJNI.new_ESLconnection__SWIG_0(host, port, user, password), true);
  }

  public ESLconnection(String host, int port, String password) {
    this(eslJNI.new_ESLconnection__SWIG_1(host, port, password), true);
  }

  public ESLconnection(String host, String port, String user, String password) {
    this(eslJNI.new_ESLconnection__SWIG_2(host, port, user, password), true);
  }

  public ESLconnection(String host, String port, String password) {
    this(eslJNI.new_ESLconnection__SWIG_3(host, port, password), true);
  }

  public ESLconnection(int socket) {
    this(eslJNI.new_ESLconnection__SWIG_4(socket), true);
  }

  public int socketDescriptor() {
    return eslJNI.ESLconnection_socketDescriptor(swigCPtr, this);
  }

  public int connected() {
    return eslJNI.ESLconnection_connected(swigCPtr, this);
  }

  public ESLevent getInfo() {
    long cPtr = eslJNI.ESLconnection_getInfo(swigCPtr, this);
    return (cPtr == 0) ? null : new ESLevent(cPtr, true);
  }

  public int send(String cmd) {
    return eslJNI.ESLconnection_send(swigCPtr, this, cmd);
  }

  public ESLevent sendRecv(String cmd) {
    long cPtr = eslJNI.ESLconnection_sendRecv(swigCPtr, this, cmd);
    return (cPtr == 0) ? null : new ESLevent(cPtr, true);
  }

  public ESLevent api(String cmd, String arg) {
    long cPtr = eslJNI.ESLconnection_api(swigCPtr, this, cmd, arg);
    return (cPtr == 0) ? null : new ESLevent(cPtr, true);
  }

  public ESLevent bgapi(String cmd, String arg, String job_uuid) {
    long cPtr = eslJNI.ESLconnection_bgapi(swigCPtr, this, cmd, arg, job_uuid);
    return (cPtr == 0) ? null : new ESLevent(cPtr, true);
  }

  public ESLevent sendEvent(ESLevent send_me) {
    long cPtr = eslJNI.ESLconnection_sendEvent(swigCPtr, this, ESLevent.getCPtr(send_me), send_me);
    return (cPtr == 0) ? null : new ESLevent(cPtr, true);
  }

  public int sendMSG(ESLevent send_me, String uuid) {
    return eslJNI.ESLconnection_sendMSG(swigCPtr, this, ESLevent.getCPtr(send_me), send_me, uuid);
  }

  public ESLevent recvEvent() {
    long cPtr = eslJNI.ESLconnection_recvEvent(swigCPtr, this);
    return (cPtr == 0) ? null : new ESLevent(cPtr, true);
  }

  public ESLevent recvEventTimed(int ms) {
    long cPtr = eslJNI.ESLconnection_recvEventTimed(swigCPtr, this, ms);
    return (cPtr == 0) ? null : new ESLevent(cPtr, true);
  }

  public ESLevent filter(String header, String value) {
    long cPtr = eslJNI.ESLconnection_filter(swigCPtr, this, header, value);
    return (cPtr == 0) ? null : new ESLevent(cPtr, true);
  }

  public int events(String etype, String value) {
    return eslJNI.ESLconnection_events(swigCPtr, this, etype, value);
  }

  public ESLevent execute(String app, String arg, String uuid) {
    long cPtr = eslJNI.ESLconnection_execute(swigCPtr, this, app, arg, uuid);
    return (cPtr == 0) ? null : new ESLevent(cPtr, true);
  }

  public ESLevent executeAsync(String app, String arg, String uuid) {
    long cPtr = eslJNI.ESLconnection_executeAsync(swigCPtr, this, app, arg, uuid);
    return (cPtr == 0) ? null : new ESLevent(cPtr, true);
  }

  public int setAsyncExecute(String val) {
    return eslJNI.ESLconnection_setAsyncExecute(swigCPtr, this, val);
  }

  public int setEventLock(String val) {
    return eslJNI.ESLconnection_setEventLock(swigCPtr, this, val);
  }

  public int disconnect() {
    return eslJNI.ESLconnection_disconnect(swigCPtr, this);
  }

}