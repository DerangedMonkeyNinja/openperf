// Code generated by go-swagger; DO NOT EDIT.

package packet_captures

// This file was generated by the swagger tool.
// Editing this file might prove futile when you re-run the swagger generate command

import (
	"context"
	"net/http"
	"time"

	"github.com/go-openapi/errors"
	"github.com/go-openapi/runtime"
	cr "github.com/go-openapi/runtime/client"
	"github.com/go-openapi/strfmt"
)

// NewBulkDeletePacketCapturesParams creates a new BulkDeletePacketCapturesParams object,
// with the default timeout for this client.
//
// Default values are not hydrated, since defaults are normally applied by the API server side.
//
// To enforce default values in parameter, use SetDefaults or WithDefaults.
func NewBulkDeletePacketCapturesParams() *BulkDeletePacketCapturesParams {
	return &BulkDeletePacketCapturesParams{
		timeout: cr.DefaultTimeout,
	}
}

// NewBulkDeletePacketCapturesParamsWithTimeout creates a new BulkDeletePacketCapturesParams object
// with the ability to set a timeout on a request.
func NewBulkDeletePacketCapturesParamsWithTimeout(timeout time.Duration) *BulkDeletePacketCapturesParams {
	return &BulkDeletePacketCapturesParams{
		timeout: timeout,
	}
}

// NewBulkDeletePacketCapturesParamsWithContext creates a new BulkDeletePacketCapturesParams object
// with the ability to set a context for a request.
func NewBulkDeletePacketCapturesParamsWithContext(ctx context.Context) *BulkDeletePacketCapturesParams {
	return &BulkDeletePacketCapturesParams{
		Context: ctx,
	}
}

// NewBulkDeletePacketCapturesParamsWithHTTPClient creates a new BulkDeletePacketCapturesParams object
// with the ability to set a custom HTTPClient for a request.
func NewBulkDeletePacketCapturesParamsWithHTTPClient(client *http.Client) *BulkDeletePacketCapturesParams {
	return &BulkDeletePacketCapturesParams{
		HTTPClient: client,
	}
}

/* BulkDeletePacketCapturesParams contains all the parameters to send to the API endpoint
   for the bulk delete packet captures operation.

   Typically these are written to a http.Request.
*/
type BulkDeletePacketCapturesParams struct {

	/* Delete.

	   Bulk delete
	*/
	Delete BulkDeletePacketCapturesBody

	timeout    time.Duration
	Context    context.Context
	HTTPClient *http.Client
}

// WithDefaults hydrates default values in the bulk delete packet captures params (not the query body).
//
// All values with no default are reset to their zero value.
func (o *BulkDeletePacketCapturesParams) WithDefaults() *BulkDeletePacketCapturesParams {
	o.SetDefaults()
	return o
}

// SetDefaults hydrates default values in the bulk delete packet captures params (not the query body).
//
// All values with no default are reset to their zero value.
func (o *BulkDeletePacketCapturesParams) SetDefaults() {
	// no default values defined for this parameter
}

// WithTimeout adds the timeout to the bulk delete packet captures params
func (o *BulkDeletePacketCapturesParams) WithTimeout(timeout time.Duration) *BulkDeletePacketCapturesParams {
	o.SetTimeout(timeout)
	return o
}

// SetTimeout adds the timeout to the bulk delete packet captures params
func (o *BulkDeletePacketCapturesParams) SetTimeout(timeout time.Duration) {
	o.timeout = timeout
}

// WithContext adds the context to the bulk delete packet captures params
func (o *BulkDeletePacketCapturesParams) WithContext(ctx context.Context) *BulkDeletePacketCapturesParams {
	o.SetContext(ctx)
	return o
}

// SetContext adds the context to the bulk delete packet captures params
func (o *BulkDeletePacketCapturesParams) SetContext(ctx context.Context) {
	o.Context = ctx
}

// WithHTTPClient adds the HTTPClient to the bulk delete packet captures params
func (o *BulkDeletePacketCapturesParams) WithHTTPClient(client *http.Client) *BulkDeletePacketCapturesParams {
	o.SetHTTPClient(client)
	return o
}

// SetHTTPClient adds the HTTPClient to the bulk delete packet captures params
func (o *BulkDeletePacketCapturesParams) SetHTTPClient(client *http.Client) {
	o.HTTPClient = client
}

// WithDelete adds the delete to the bulk delete packet captures params
func (o *BulkDeletePacketCapturesParams) WithDelete(delete BulkDeletePacketCapturesBody) *BulkDeletePacketCapturesParams {
	o.SetDelete(delete)
	return o
}

// SetDelete adds the delete to the bulk delete packet captures params
func (o *BulkDeletePacketCapturesParams) SetDelete(delete BulkDeletePacketCapturesBody) {
	o.Delete = delete
}

// WriteToRequest writes these params to a swagger request
func (o *BulkDeletePacketCapturesParams) WriteToRequest(r runtime.ClientRequest, reg strfmt.Registry) error {

	if err := r.SetTimeout(o.timeout); err != nil {
		return err
	}
	var res []error
	if err := r.SetBodyParam(o.Delete); err != nil {
		return err
	}

	if len(res) > 0 {
		return errors.CompositeValidationError(res...)
	}
	return nil
}
