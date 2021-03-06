// Code generated by go-swagger; DO NOT EDIT.

package t_v_l_p

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

// NewDeleteTvlpResultParams creates a new DeleteTvlpResultParams object,
// with the default timeout for this client.
//
// Default values are not hydrated, since defaults are normally applied by the API server side.
//
// To enforce default values in parameter, use SetDefaults or WithDefaults.
func NewDeleteTvlpResultParams() *DeleteTvlpResultParams {
	return &DeleteTvlpResultParams{
		timeout: cr.DefaultTimeout,
	}
}

// NewDeleteTvlpResultParamsWithTimeout creates a new DeleteTvlpResultParams object
// with the ability to set a timeout on a request.
func NewDeleteTvlpResultParamsWithTimeout(timeout time.Duration) *DeleteTvlpResultParams {
	return &DeleteTvlpResultParams{
		timeout: timeout,
	}
}

// NewDeleteTvlpResultParamsWithContext creates a new DeleteTvlpResultParams object
// with the ability to set a context for a request.
func NewDeleteTvlpResultParamsWithContext(ctx context.Context) *DeleteTvlpResultParams {
	return &DeleteTvlpResultParams{
		Context: ctx,
	}
}

// NewDeleteTvlpResultParamsWithHTTPClient creates a new DeleteTvlpResultParams object
// with the ability to set a custom HTTPClient for a request.
func NewDeleteTvlpResultParamsWithHTTPClient(client *http.Client) *DeleteTvlpResultParams {
	return &DeleteTvlpResultParams{
		HTTPClient: client,
	}
}

/* DeleteTvlpResultParams contains all the parameters to send to the API endpoint
   for the delete tvlp result operation.

   Typically these are written to a http.Request.
*/
type DeleteTvlpResultParams struct {

	/* ID.

	   Unique resource identifier

	   Format: string
	*/
	ID string

	timeout    time.Duration
	Context    context.Context
	HTTPClient *http.Client
}

// WithDefaults hydrates default values in the delete tvlp result params (not the query body).
//
// All values with no default are reset to their zero value.
func (o *DeleteTvlpResultParams) WithDefaults() *DeleteTvlpResultParams {
	o.SetDefaults()
	return o
}

// SetDefaults hydrates default values in the delete tvlp result params (not the query body).
//
// All values with no default are reset to their zero value.
func (o *DeleteTvlpResultParams) SetDefaults() {
	// no default values defined for this parameter
}

// WithTimeout adds the timeout to the delete tvlp result params
func (o *DeleteTvlpResultParams) WithTimeout(timeout time.Duration) *DeleteTvlpResultParams {
	o.SetTimeout(timeout)
	return o
}

// SetTimeout adds the timeout to the delete tvlp result params
func (o *DeleteTvlpResultParams) SetTimeout(timeout time.Duration) {
	o.timeout = timeout
}

// WithContext adds the context to the delete tvlp result params
func (o *DeleteTvlpResultParams) WithContext(ctx context.Context) *DeleteTvlpResultParams {
	o.SetContext(ctx)
	return o
}

// SetContext adds the context to the delete tvlp result params
func (o *DeleteTvlpResultParams) SetContext(ctx context.Context) {
	o.Context = ctx
}

// WithHTTPClient adds the HTTPClient to the delete tvlp result params
func (o *DeleteTvlpResultParams) WithHTTPClient(client *http.Client) *DeleteTvlpResultParams {
	o.SetHTTPClient(client)
	return o
}

// SetHTTPClient adds the HTTPClient to the delete tvlp result params
func (o *DeleteTvlpResultParams) SetHTTPClient(client *http.Client) {
	o.HTTPClient = client
}

// WithID adds the id to the delete tvlp result params
func (o *DeleteTvlpResultParams) WithID(id string) *DeleteTvlpResultParams {
	o.SetID(id)
	return o
}

// SetID adds the id to the delete tvlp result params
func (o *DeleteTvlpResultParams) SetID(id string) {
	o.ID = id
}

// WriteToRequest writes these params to a swagger request
func (o *DeleteTvlpResultParams) WriteToRequest(r runtime.ClientRequest, reg strfmt.Registry) error {

	if err := r.SetTimeout(o.timeout); err != nil {
		return err
	}
	var res []error

	// path param id
	if err := r.SetPathParam("id", o.ID); err != nil {
		return err
	}

	if len(res) > 0 {
		return errors.CompositeValidationError(res...)
	}
	return nil
}
